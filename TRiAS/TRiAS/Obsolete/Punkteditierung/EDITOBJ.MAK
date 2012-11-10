# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=edobj32 - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to edobj32 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "edobj32 - Win32 Release" && "$(CFG)" !=\
 "edobj32 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "EDITOBJ.MAK" CFG="edobj32 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "edobj32 - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "edobj32 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "edobj32 - Win32 Debug"
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "edobj32 - Win32 Release"

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
TargetName=editobj
# End Custom Macros

ALL : "$(OUTDIR)\editobj.ext" "c:\trias.mvc\trias200.rel\editobj.ext"

CLEAN : 
	-@erase "$(INTDIR)\dblnumex.obj"
	-@erase "$(INTDIR)\EDITOBJ.OBJ"
	-@erase "$(INTDIR)\EDITOBJ.pch"
	-@erase "$(INTDIR)\EDITOBJP.OBJ"
	-@erase "$(INTDIR)\EDITPNT.OBJ"
	-@erase "$(INTDIR)\edobj32.res"
	-@erase "$(INTDIR)\IDENTLST.OBJ"
	-@erase "$(INTDIR)\PNTMENU.OBJ"
	-@erase "$(INTDIR)\SHIFT.OBJ"
	-@erase "$(INTDIR)\STRUTIL.OBJ"
	-@erase "$(INTDIR)\uiowner.obj"
	-@erase "$(OUTDIR)\editobj.exp"
	-@erase "$(OUTDIR)\editobj.ext"
	-@erase "$(OUTDIR)\editobj.lib"
	-@erase "c:\trias.mvc\trias200.rel\editobj.ext"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

.\WinRel\edobj32.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTENSNDLL__" /D "__CV__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /Yu"editobjp.hxx" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "DLL" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTENSNDLL__" /D\
 "__CV__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION"\
 /Fp"$(INTDIR)/EDITOBJ.pch" /Yu"editobjp.hxx" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /i ".." /d "NDEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/edobj32.res" /i ".." /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/EDITOBJ.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ixtnsr40.lib stdcppr.lib tfrmwork.lib cont32r.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /stub:"obj32/rights.exe" /out:"Release\editobj.ext" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=ixtnsr40.lib stdcppr.lib tfrmwork.lib cont32r.lib kernel32.lib\
 user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib\
 ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll\
 /incremental:no /pdb:"$(OUTDIR)/editobj.pdb" /machine:I386\
 /def:".\OBJ32\EDOBJ32.DEF" /stub:"obj32/rights.exe"\
 /out:"$(OUTDIR)/editobj.ext" /implib:"$(OUTDIR)/editobj.lib"\
 /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\OBJ32\EDOBJ32.DEF"
LINK32_OBJS= \
	"$(INTDIR)\dblnumex.obj" \
	"$(INTDIR)\EDITOBJ.OBJ" \
	"$(INTDIR)\EDITOBJP.OBJ" \
	"$(INTDIR)\EDITPNT.OBJ" \
	"$(INTDIR)\edobj32.res" \
	"$(INTDIR)\IDENTLST.OBJ" \
	"$(INTDIR)\PNTMENU.OBJ" \
	"$(INTDIR)\SHIFT.OBJ" \
	"$(INTDIR)\STRUTIL.OBJ" \
	"$(INTDIR)\uiowner.obj"

"$(OUTDIR)\editobj.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
TargetPath=.\Release\editobj.ext
TargetName=editobj
InputPath=.\Release\editobj.ext
SOURCE=$(InputPath)

"c:\trias.mvc\trias200.rel\$(TargetName).ext" : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
   copy "$(TargetPath)" c:\trias.mvc\trias200.rel

# End Custom Build

!ELSEIF  "$(CFG)" == "edobj32 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
TargetName=editobjd
# End Custom Macros

ALL : "$(OUTDIR)\editobjd.ext" "$(OUTDIR)\EDITOBJ.bsc"\
 "c:\trias.mvc\trias200\editobjd.ext"

CLEAN : 
	-@erase "$(INTDIR)\dblnumex.obj"
	-@erase "$(INTDIR)\dblnumex.sbr"
	-@erase "$(INTDIR)\EDITOBJ.OBJ"
	-@erase "$(INTDIR)\EDITOBJ.SBR"
	-@erase "$(INTDIR)\editobjd.idb"
	-@erase "$(INTDIR)\editobjd.pch"
	-@erase "$(INTDIR)\editobjd.pdb"
	-@erase "$(INTDIR)\EDITOBJP.OBJ"
	-@erase "$(INTDIR)\EDITOBJP.SBR"
	-@erase "$(INTDIR)\EDITPNT.OBJ"
	-@erase "$(INTDIR)\EDITPNT.SBR"
	-@erase "$(INTDIR)\edobj32.res"
	-@erase "$(INTDIR)\IDENTLST.OBJ"
	-@erase "$(INTDIR)\IDENTLST.SBR"
	-@erase "$(INTDIR)\PNTMENU.OBJ"
	-@erase "$(INTDIR)\PNTMENU.SBR"
	-@erase "$(INTDIR)\SHIFT.OBJ"
	-@erase "$(INTDIR)\SHIFT.SBR"
	-@erase "$(INTDIR)\STRUTIL.OBJ"
	-@erase "$(INTDIR)\STRUTIL.SBR"
	-@erase "$(INTDIR)\uiowner.obj"
	-@erase "$(INTDIR)\uiowner.sbr"
	-@erase "$(OUTDIR)\EDITOBJ.bsc"
	-@erase "$(OUTDIR)\editobjd.exp"
	-@erase "$(OUTDIR)\editobjd.ext"
	-@erase "$(OUTDIR)\editobjd.ilk"
	-@erase "$(OUTDIR)\editobjd.lib"
	-@erase "c:\trias.mvc\trias200\editobjd.ext"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

.\WinDebug\edobj32.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTENSNDLL__" /D "__CV__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /FR /Fp"Debug/editobjd.pch" /Yu"editobjp.hxx" /Fd"Debug/editobjd.pdb" /c
CPP_PROJ=/nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "DLL" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D\
 "__XTENSNDLL__" /D "__CV__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D\
 "QI_EXCEPTION" /FR"$(INTDIR)/" /Fp"$(INTDIR)/editobjd.pch" /Yu"editobjp.hxx"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/editobjd.pdb" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /i ".." /d "_DEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/edobj32.res" /i ".." /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/EDITOBJ.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\dblnumex.sbr" \
	"$(INTDIR)\EDITOBJ.SBR" \
	"$(INTDIR)\EDITOBJP.SBR" \
	"$(INTDIR)\EDITPNT.SBR" \
	"$(INTDIR)\IDENTLST.SBR" \
	"$(INTDIR)\PNTMENU.SBR" \
	"$(INTDIR)\SHIFT.SBR" \
	"$(INTDIR)\STRUTIL.SBR" \
	"$(INTDIR)\uiowner.sbr"

"$(OUTDIR)\EDITOBJ.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 ixtnsd40.lib stdcppd.lib tfrm32d.lib cont32d.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /stub:"obj32/rights.exe" /out:"Debug/editobjd.ext" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=ixtnsd40.lib stdcppd.lib tfrm32d.lib cont32d.lib kernel32.lib\
 user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib\
 ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll\
 /incremental:yes /pdb:"$(OUTDIR)/editobjd.pdb" /debug /machine:I386\
 /def:".\OBJ32\EDOBJ32.DEF" /stub:"obj32/rights.exe"\
 /out:"$(OUTDIR)/editobjd.ext" /implib:"$(OUTDIR)/editobjd.lib"\
 /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\OBJ32\EDOBJ32.DEF"
LINK32_OBJS= \
	"$(INTDIR)\dblnumex.obj" \
	"$(INTDIR)\EDITOBJ.OBJ" \
	"$(INTDIR)\EDITOBJP.OBJ" \
	"$(INTDIR)\EDITPNT.OBJ" \
	"$(INTDIR)\edobj32.res" \
	"$(INTDIR)\IDENTLST.OBJ" \
	"$(INTDIR)\PNTMENU.OBJ" \
	"$(INTDIR)\SHIFT.OBJ" \
	"$(INTDIR)\STRUTIL.OBJ" \
	"$(INTDIR)\uiowner.obj"

"$(OUTDIR)\editobjd.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
TargetPath=.\Debug\editobjd.ext
TargetName=editobjd
InputPath=.\Debug\editobjd.ext
SOURCE=$(InputPath)

"c:\trias.mvc\trias200\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   copy "$(TargetPath)" c:\trias.mvc\trias200

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

# Name "edobj32 - Win32 Release"
# Name "edobj32 - Win32 Debug"

!IF  "$(CFG)" == "edobj32 - Win32 Release"

!ELSEIF  "$(CFG)" == "edobj32 - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\SHIFT.CXX
DEP_CPP_SHIFT=\
	".\editobj.hxx"\
	".\editobjp.hxx"\
	".\identlst.hxx"\
	".\shift.hxx"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
	{$(INCLUDE)}"\cstddef"\
	{$(INCLUDE)}"\cstdio"\
	{$(INCLUDE)}"\cstdlib"\
	{$(INCLUDE)}"\cstring"\
	{$(INCLUDE)}"\cwchar"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\exception"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\ios"\
	{$(INCLUDE)}"\iosfwd"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\iunredo.hxx"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\stdexcept"\
	{$(INCLUDE)}"\streambuf"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\typeinfo"\
	{$(INCLUDE)}"\use_ansi.h"\
	{$(INCLUDE)}"\utility"\
	{$(INCLUDE)}"\xiosbase"\
	{$(INCLUDE)}"\xlocale"\
	{$(INCLUDE)}"\xlocinfo"\
	{$(INCLUDE)}"\xlocinfo.h"\
	{$(INCLUDE)}"\xlocnum"\
	{$(INCLUDE)}"\xmemory"\
	{$(INCLUDE)}"\xstddef"\
	{$(INCLUDE)}"\xstring"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	

!IF  "$(CFG)" == "edobj32 - Win32 Release"


"$(INTDIR)\SHIFT.OBJ" : $(SOURCE) $(DEP_CPP_SHIFT) "$(INTDIR)"\
 "$(INTDIR)\EDITOBJ.pch"


!ELSEIF  "$(CFG)" == "edobj32 - Win32 Debug"


"$(INTDIR)\SHIFT.OBJ" : $(SOURCE) $(DEP_CPP_SHIFT) "$(INTDIR)"\
 "$(INTDIR)\editobjd.pch"

"$(INTDIR)\SHIFT.SBR" : $(SOURCE) $(DEP_CPP_SHIFT) "$(INTDIR)"\
 "$(INTDIR)\editobjd.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PNTMENU.CXX
DEP_CPP_PNTME=\
	".\editobj.hxx"\
	".\editobjp.hxx"\
	".\editobjr.h"\
	".\editpnt.hxx"\
	".\identlst.hxx"\
	".\obj32\editobj.h"\
	".\shift.hxx"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
	{$(INCLUDE)}"\cstddef"\
	{$(INCLUDE)}"\cstdio"\
	{$(INCLUDE)}"\cstdlib"\
	{$(INCLUDE)}"\cstring"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTFX.HXX"\
	{$(INCLUDE)}"\cwchar"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\exception"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\ios"\
	{$(INCLUDE)}"\iosfwd"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\iunredo.hxx"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\stdexcept"\
	{$(INCLUDE)}"\streambuf"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\typeinfo"\
	{$(INCLUDE)}"\undoguid.h"\
	{$(INCLUDE)}"\use_ansi.h"\
	{$(INCLUDE)}"\utility"\
	{$(INCLUDE)}"\xiosbase"\
	{$(INCLUDE)}"\xlocale"\
	{$(INCLUDE)}"\xlocinfo"\
	{$(INCLUDE)}"\xlocinfo.h"\
	{$(INCLUDE)}"\xlocnum"\
	{$(INCLUDE)}"\xmemory"\
	{$(INCLUDE)}"\xstddef"\
	{$(INCLUDE)}"\xstring"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	
NODEP_CPP_PNTME=\
	".\editobj.h"\
	

!IF  "$(CFG)" == "edobj32 - Win32 Release"


"$(INTDIR)\PNTMENU.OBJ" : $(SOURCE) $(DEP_CPP_PNTME) "$(INTDIR)"\
 "$(INTDIR)\EDITOBJ.pch"


!ELSEIF  "$(CFG)" == "edobj32 - Win32 Debug"


"$(INTDIR)\PNTMENU.OBJ" : $(SOURCE) $(DEP_CPP_PNTME) "$(INTDIR)"\
 "$(INTDIR)\editobjd.pch"

"$(INTDIR)\PNTMENU.SBR" : $(SOURCE) $(DEP_CPP_PNTME) "$(INTDIR)"\
 "$(INTDIR)\editobjd.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EDITOBJ.CXX

!IF  "$(CFG)" == "edobj32 - Win32 Release"

DEP_CPP_EDITO=\
	".\editobj.hxx"\
	".\editobjp.hxx"\
	".\editobjr.h"\
	".\edptguid.h"\
	".\identlst.hxx"\
	".\obj32\editobj.h"\
	".\obj32\versio32.h"\
	".\shift.hxx"\
	".\UIOwner.h"\
	".\version.h"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
	{$(INCLUDE)}"\cstddef"\
	{$(INCLUDE)}"\cstdio"\
	{$(INCLUDE)}"\cstdlib"\
	{$(INCLUDE)}"\cstring"\
	{$(INCLUDE)}"\cwchar"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\exception"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\ios"\
	{$(INCLUDE)}"\iosfwd"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\Itoolbar.h"\
	{$(INCLUDE)}"\iunredo.hxx"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\stdexcept"\
	{$(INCLUDE)}"\streambuf"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\toolguid.h"\
	{$(INCLUDE)}"\typeinfo"\
	{$(INCLUDE)}"\undoguid.h"\
	{$(INCLUDE)}"\use_ansi.h"\
	{$(INCLUDE)}"\utility"\
	{$(INCLUDE)}"\xiosbase"\
	{$(INCLUDE)}"\xlocale"\
	{$(INCLUDE)}"\xlocinfo"\
	{$(INCLUDE)}"\xlocinfo.h"\
	{$(INCLUDE)}"\xlocnum"\
	{$(INCLUDE)}"\xmemory"\
	{$(INCLUDE)}"\xstddef"\
	{$(INCLUDE)}"\xstring"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	
NODEP_CPP_EDITO=\
	".\editobj.h"\
	".\versio16.h"\
	

"$(INTDIR)\EDITOBJ.OBJ" : $(SOURCE) $(DEP_CPP_EDITO) "$(INTDIR)"\
 "$(INTDIR)\EDITOBJ.pch"


!ELSEIF  "$(CFG)" == "edobj32 - Win32 Debug"

DEP_CPP_EDITO=\
	".\editobj.hxx"\
	".\editobjp.hxx"\
	".\editobjr.h"\
	".\edptguid.h"\
	".\identlst.hxx"\
	".\obj32\editobj.h"\
	".\obj32\versio32.h"\
	".\shift.hxx"\
	".\UIOwner.h"\
	".\versio16.h"\
	".\version.h"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
	{$(INCLUDE)}"\cstddef"\
	{$(INCLUDE)}"\cstdio"\
	{$(INCLUDE)}"\cstdlib"\
	{$(INCLUDE)}"\cstring"\
	{$(INCLUDE)}"\cwchar"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\exception"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\ios"\
	{$(INCLUDE)}"\iosfwd"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\Itoolbar.h"\
	{$(INCLUDE)}"\iunredo.hxx"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\stdexcept"\
	{$(INCLUDE)}"\streambuf"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\toolguid.h"\
	{$(INCLUDE)}"\typeinfo"\
	{$(INCLUDE)}"\undoguid.h"\
	{$(INCLUDE)}"\use_ansi.h"\
	{$(INCLUDE)}"\utility"\
	{$(INCLUDE)}"\xiosbase"\
	{$(INCLUDE)}"\xlocale"\
	{$(INCLUDE)}"\xlocinfo"\
	{$(INCLUDE)}"\xlocinfo.h"\
	{$(INCLUDE)}"\xlocnum"\
	{$(INCLUDE)}"\xmemory"\
	{$(INCLUDE)}"\xstddef"\
	{$(INCLUDE)}"\xstring"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	
NODEP_CPP_EDITO=\
	".\editobj.h"\
	

"$(INTDIR)\EDITOBJ.OBJ" : $(SOURCE) $(DEP_CPP_EDITO) "$(INTDIR)"\
 "$(INTDIR)\editobjd.pch"

"$(INTDIR)\EDITOBJ.SBR" : $(SOURCE) $(DEP_CPP_EDITO) "$(INTDIR)"\
 "$(INTDIR)\editobjd.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\IDENTLST.CXX
DEP_CPP_IDENT=\
	".\editobj.hxx"\
	".\editobjp.hxx"\
	".\identlst.hxx"\
	".\shift.hxx"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
	{$(INCLUDE)}"\cstddef"\
	{$(INCLUDE)}"\cstdio"\
	{$(INCLUDE)}"\cstdlib"\
	{$(INCLUDE)}"\cstring"\
	{$(INCLUDE)}"\cwchar"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\exception"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\ios"\
	{$(INCLUDE)}"\iosfwd"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\iunredo.hxx"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\stdexcept"\
	{$(INCLUDE)}"\streambuf"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\typeinfo"\
	{$(INCLUDE)}"\use_ansi.h"\
	{$(INCLUDE)}"\utility"\
	{$(INCLUDE)}"\xiosbase"\
	{$(INCLUDE)}"\xlocale"\
	{$(INCLUDE)}"\xlocinfo"\
	{$(INCLUDE)}"\xlocinfo.h"\
	{$(INCLUDE)}"\xlocnum"\
	{$(INCLUDE)}"\xmemory"\
	{$(INCLUDE)}"\xstddef"\
	{$(INCLUDE)}"\xstring"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	

!IF  "$(CFG)" == "edobj32 - Win32 Release"


"$(INTDIR)\IDENTLST.OBJ" : $(SOURCE) $(DEP_CPP_IDENT) "$(INTDIR)"\
 "$(INTDIR)\EDITOBJ.pch"


!ELSEIF  "$(CFG)" == "edobj32 - Win32 Debug"


"$(INTDIR)\IDENTLST.OBJ" : $(SOURCE) $(DEP_CPP_IDENT) "$(INTDIR)"\
 "$(INTDIR)\editobjd.pch"

"$(INTDIR)\IDENTLST.SBR" : $(SOURCE) $(DEP_CPP_IDENT) "$(INTDIR)"\
 "$(INTDIR)\editobjd.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EDITPNT.CXX
DEP_CPP_EDITP=\
	".\editobj.hxx"\
	".\editobjp.hxx"\
	".\editpnt.h"\
	".\editpnt.hxx"\
	".\identlst.hxx"\
	".\shift.hxx"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
	{$(INCLUDE)}"\cstddef"\
	{$(INCLUDE)}"\cstdio"\
	{$(INCLUDE)}"\cstdlib"\
	{$(INCLUDE)}"\cstring"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTFX.HXX"\
	{$(INCLUDE)}"\cwchar"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\exception"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\ios"\
	{$(INCLUDE)}"\iosfwd"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\iunredo.hxx"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\stdexcept"\
	{$(INCLUDE)}"\streambuf"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\typeinfo"\
	{$(INCLUDE)}"\use_ansi.h"\
	{$(INCLUDE)}"\utility"\
	{$(INCLUDE)}"\xiosbase"\
	{$(INCLUDE)}"\xlocale"\
	{$(INCLUDE)}"\xlocinfo"\
	{$(INCLUDE)}"\xlocinfo.h"\
	{$(INCLUDE)}"\xlocnum"\
	{$(INCLUDE)}"\xmemory"\
	{$(INCLUDE)}"\xstddef"\
	{$(INCLUDE)}"\xstring"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	

!IF  "$(CFG)" == "edobj32 - Win32 Release"


"$(INTDIR)\EDITPNT.OBJ" : $(SOURCE) $(DEP_CPP_EDITP) "$(INTDIR)"\
 "$(INTDIR)\EDITOBJ.pch"


!ELSEIF  "$(CFG)" == "edobj32 - Win32 Debug"


"$(INTDIR)\EDITPNT.OBJ" : $(SOURCE) $(DEP_CPP_EDITP) "$(INTDIR)"\
 "$(INTDIR)\editobjd.pch"

"$(INTDIR)\EDITPNT.SBR" : $(SOURCE) $(DEP_CPP_EDITP) "$(INTDIR)"\
 "$(INTDIR)\editobjd.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EDITOBJP.CXX
DEP_CPP_EDITOB=\
	".\editobj.hxx"\
	".\editobjp.hxx"\
	".\identlst.hxx"\
	".\shift.hxx"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
	{$(INCLUDE)}"\cstddef"\
	{$(INCLUDE)}"\cstdio"\
	{$(INCLUDE)}"\cstdlib"\
	{$(INCLUDE)}"\cstring"\
	{$(INCLUDE)}"\cwchar"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\exception"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\ios"\
	{$(INCLUDE)}"\iosfwd"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\iunredo.hxx"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\ospace\com\atl.h"\
	{$(INCLUDE)}"\ospace\com\atlbase.h"\
	{$(INCLUDE)}"\ospace\com\atlcom.h"\
	{$(INCLUDE)}"\ospace\com\atlcomx.h"\
	{$(INCLUDE)}"\ospace\com\atlimpl.h"\
	{$(INCLUDE)}"\ospace\com\atlutil.h"\
	{$(INCLUDE)}"\ospace\com\smartif.h"\
	{$(INCLUDE)}"\ospace\com\src\atlimpl.cpp"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\stdexcept"\
	{$(INCLUDE)}"\streambuf"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\typeinfo"\
	{$(INCLUDE)}"\use_ansi.h"\
	{$(INCLUDE)}"\utility"\
	{$(INCLUDE)}"\xiosbase"\
	{$(INCLUDE)}"\xlocale"\
	{$(INCLUDE)}"\xlocinfo"\
	{$(INCLUDE)}"\xlocinfo.h"\
	{$(INCLUDE)}"\xlocnum"\
	{$(INCLUDE)}"\xmemory"\
	{$(INCLUDE)}"\xstddef"\
	{$(INCLUDE)}"\xstring"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	

!IF  "$(CFG)" == "edobj32 - Win32 Release"

# ADD CPP /Yc"editobjp.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "DLL" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTENSNDLL__" /D\
 "__CV__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION"\
 /Fp"$(INTDIR)/EDITOBJ.pch" /Yc"editobjp.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\EDITOBJP.OBJ" : $(SOURCE) $(DEP_CPP_EDITOB) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\EDITOBJ.pch" : $(SOURCE) $(DEP_CPP_EDITOB) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "edobj32 - Win32 Debug"

# ADD CPP /Yc"editobjp.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "DLL" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D\
 "__XTENSNDLL__" /D "__CV__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D\
 "QI_EXCEPTION" /FR"$(INTDIR)/" /Fp"$(INTDIR)/editobjd.pch" /Yc"editobjp.hxx"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/editobjd.pdb" /c $(SOURCE) \
	

"$(INTDIR)\EDITOBJP.OBJ" : $(SOURCE) $(DEP_CPP_EDITOB) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\EDITOBJP.SBR" : $(SOURCE) $(DEP_CPP_EDITOB) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\editobjd.pch" : $(SOURCE) $(DEP_CPP_EDITOB) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRUTIL.CXX
DEP_CPP_STRUT=\
	".\editobj.hxx"\
	".\editobjp.hxx"\
	".\identlst.hxx"\
	".\shift.hxx"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
	{$(INCLUDE)}"\cstddef"\
	{$(INCLUDE)}"\cstdio"\
	{$(INCLUDE)}"\cstdlib"\
	{$(INCLUDE)}"\cstring"\
	{$(INCLUDE)}"\cwchar"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\exception"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\ios"\
	{$(INCLUDE)}"\iosfwd"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\iunredo.hxx"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\stdexcept"\
	{$(INCLUDE)}"\streambuf"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\typeinfo"\
	{$(INCLUDE)}"\use_ansi.h"\
	{$(INCLUDE)}"\utility"\
	{$(INCLUDE)}"\xiosbase"\
	{$(INCLUDE)}"\xlocale"\
	{$(INCLUDE)}"\xlocinfo"\
	{$(INCLUDE)}"\xlocinfo.h"\
	{$(INCLUDE)}"\xlocnum"\
	{$(INCLUDE)}"\xmemory"\
	{$(INCLUDE)}"\xstddef"\
	{$(INCLUDE)}"\xstring"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	

!IF  "$(CFG)" == "edobj32 - Win32 Release"


"$(INTDIR)\STRUTIL.OBJ" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"\
 "$(INTDIR)\EDITOBJ.pch"


!ELSEIF  "$(CFG)" == "edobj32 - Win32 Debug"


"$(INTDIR)\STRUTIL.OBJ" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"\
 "$(INTDIR)\editobjd.pch"

"$(INTDIR)\STRUTIL.SBR" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"\
 "$(INTDIR)\editobjd.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dblnumex.cxx
DEP_CPP_DBLNU=\
	".\editobj.hxx"\
	".\editobjp.hxx"\
	".\identlst.hxx"\
	".\shift.hxx"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
	{$(INCLUDE)}"\cstddef"\
	{$(INCLUDE)}"\cstdio"\
	{$(INCLUDE)}"\cstdlib"\
	{$(INCLUDE)}"\cstring"\
	{$(INCLUDE)}"\cwchar"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\exception"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\ios"\
	{$(INCLUDE)}"\iosfwd"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\iunredo.hxx"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\stdexcept"\
	{$(INCLUDE)}"\streambuf"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\typeinfo"\
	{$(INCLUDE)}"\use_ansi.h"\
	{$(INCLUDE)}"\utility"\
	{$(INCLUDE)}"\xiosbase"\
	{$(INCLUDE)}"\xlocale"\
	{$(INCLUDE)}"\xlocinfo"\
	{$(INCLUDE)}"\xlocinfo.h"\
	{$(INCLUDE)}"\xlocnum"\
	{$(INCLUDE)}"\xmemory"\
	{$(INCLUDE)}"\xstddef"\
	{$(INCLUDE)}"\xstring"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	

!IF  "$(CFG)" == "edobj32 - Win32 Release"


"$(INTDIR)\dblnumex.obj" : $(SOURCE) $(DEP_CPP_DBLNU) "$(INTDIR)"\
 "$(INTDIR)\EDITOBJ.pch"


!ELSEIF  "$(CFG)" == "edobj32 - Win32 Debug"


"$(INTDIR)\dblnumex.obj" : $(SOURCE) $(DEP_CPP_DBLNU) "$(INTDIR)"\
 "$(INTDIR)\editobjd.pch"

"$(INTDIR)\dblnumex.sbr" : $(SOURCE) $(DEP_CPP_DBLNU) "$(INTDIR)"\
 "$(INTDIR)\editobjd.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\uiowner.cpp
DEP_CPP_UIOWN=\
	".\editobj.hxx"\
	".\editobjp.hxx"\
	".\editobjr.h"\
	".\identlst.hxx"\
	".\obj32\editobj.h"\
	".\shift.hxx"\
	".\UIOwner.h"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
	{$(INCLUDE)}"\cstddef"\
	{$(INCLUDE)}"\cstdio"\
	{$(INCLUDE)}"\cstdlib"\
	{$(INCLUDE)}"\cstring"\
	{$(INCLUDE)}"\cwchar"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\exception"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\ios"\
	{$(INCLUDE)}"\iosfwd"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\Itoolbar.h"\
	{$(INCLUDE)}"\iunredo.hxx"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\ospace\com\atl.h"\
	{$(INCLUDE)}"\ospace\com\atlbase.h"\
	{$(INCLUDE)}"\ospace\com\atlcom.h"\
	{$(INCLUDE)}"\ospace\com\atlcomx.h"\
	{$(INCLUDE)}"\ospace\com\atlutil.h"\
	{$(INCLUDE)}"\ospace\com\smartif.h"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\stdexcept"\
	{$(INCLUDE)}"\streambuf"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\toolguid.h"\
	{$(INCLUDE)}"\typeinfo"\
	{$(INCLUDE)}"\use_ansi.h"\
	{$(INCLUDE)}"\utility"\
	{$(INCLUDE)}"\xiosbase"\
	{$(INCLUDE)}"\xlocale"\
	{$(INCLUDE)}"\xlocinfo"\
	{$(INCLUDE)}"\xlocinfo.h"\
	{$(INCLUDE)}"\xlocnum"\
	{$(INCLUDE)}"\xmemory"\
	{$(INCLUDE)}"\xstddef"\
	{$(INCLUDE)}"\xstring"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	
NODEP_CPP_UIOWN=\
	".\editobj.h"\
	

!IF  "$(CFG)" == "edobj32 - Win32 Release"


"$(INTDIR)\uiowner.obj" : $(SOURCE) $(DEP_CPP_UIOWN) "$(INTDIR)"\
 "$(INTDIR)\EDITOBJ.pch"


!ELSEIF  "$(CFG)" == "edobj32 - Win32 Debug"


"$(INTDIR)\uiowner.obj" : $(SOURCE) $(DEP_CPP_UIOWN) "$(INTDIR)"\
 "$(INTDIR)\editobjd.pch"

"$(INTDIR)\uiowner.sbr" : $(SOURCE) $(DEP_CPP_UIOWN) "$(INTDIR)"\
 "$(INTDIR)\editobjd.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OBJ32\EDOBJ32.DEF

!IF  "$(CFG)" == "edobj32 - Win32 Release"

!ELSEIF  "$(CFG)" == "edobj32 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OBJ32\edobj32.RC
DEP_RSC_EDOBJ=\
	".\OBJ32\bitmap2.bmp"\
	".\obj32\editobj.h"\
	".\OBJ32\edobj32.rcv"\
	".\OBJ32\STIFTP.BMP"\
	".\OBJ32\Toolbar.bmp"\
	{$(INCLUDE)}"\RESSTRG.H"\
	
NODEP_RSC_EDOBJ=\
	".\OBJ32\editpnt.h"\
	

!IF  "$(CFG)" == "edobj32 - Win32 Release"


"$(INTDIR)\edobj32.res" : $(SOURCE) $(DEP_RSC_EDOBJ) "$(INTDIR)"
   $(RSC) /l 0x407 /fo"$(INTDIR)/edobj32.res" /i ".." /i "OBJ32" /d "NDEBUG"\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "edobj32 - Win32 Debug"


"$(INTDIR)\edobj32.res" : $(SOURCE) $(DEP_RSC_EDOBJ) "$(INTDIR)"
   $(RSC) /l 0x407 /fo"$(INTDIR)/edobj32.res" /i ".." /i "OBJ32" /d "_DEBUG"\
 $(SOURCE)


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
