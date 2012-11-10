# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=SIMPLE - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to SIMPLE - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "SIMPLE - Win32 Release" && "$(CFG)" != "SIMPLE - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "SIMPLE.MAK" CFG="SIMPLE - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SIMPLE - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "SIMPLE - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "SIMPLE - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WinRel"
# PROP Intermediate_Dir "WinRel"
OUTDIR=.\WinRel
INTDIR=.\WinRel

ALL : "$(OUTDIR)\simple.ext" "$(OUTDIR)\SIMPLE.bsc"

CLEAN : 
	-@erase "$(INTDIR)\SIMPLE.OBJ"
	-@erase "$(INTDIR)\SIMPLE.pch"
	-@erase "$(INTDIR)\SIMPLE.res"
	-@erase "$(INTDIR)\SIMPLE.SBR"
	-@erase "$(INTDIR)\SIMPLEP.OBJ"
	-@erase "$(INTDIR)\SIMPLEP.SBR"
	-@erase "$(OUTDIR)\SIMPLE.bsc"
	-@erase "$(OUTDIR)\simple.exp"
	-@erase "$(OUTDIR)\simple.ext"
	-@erase "$(OUTDIR)\simple.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "__CV__" /D "STRICT" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /FR /Yu"simplep.hxx" /c
CPP_PROJ=/nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__CV__" /D "STRICT" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__"\
 /FR"$(INTDIR)/" /Fp"$(INTDIR)/SIMPLE.pch" /Yu"simplep.hxx" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\WinRel/
CPP_SBRS=.\WinRel/
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/SIMPLE.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SIMPLE.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\SIMPLE.SBR" \
	"$(INTDIR)\SIMPLEP.SBR"

"$(OUTDIR)\SIMPLE.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 IxtAtr42.lib stdcppr.lib tfrmwork.lib cont32r.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386 /stub:"rights.exe" /out:"WinRel/simple.ext"
LINK32_FLAGS=IxtAtr42.lib stdcppr.lib tfrmwork.lib cont32r.lib kernel32.lib\
 user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib\
 ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo\
 /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)/simple.pdb"\
 /machine:I386 /def:".\SIMPLE.DEF" /stub:"rights.exe"\
 /out:"$(OUTDIR)/simple.ext" /implib:"$(OUTDIR)/simple.lib" 
DEF_FILE= \
	".\SIMPLE.DEF"
LINK32_OBJS= \
	"$(INTDIR)\SIMPLE.OBJ" \
	"$(INTDIR)\SIMPLE.res" \
	"$(INTDIR)\SIMPLEP.OBJ"

"$(OUTDIR)\simple.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SIMPLE - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinDebug"
# PROP Intermediate_Dir "WinDebug"
OUTDIR=.\WinDebug
INTDIR=.\WinDebug

ALL : "$(OUTDIR)\simple.ext" "$(OUTDIR)\SIMPLE.bsc"

CLEAN : 
	-@erase "$(INTDIR)\SIMPLE.OBJ"
	-@erase "$(INTDIR)\SIMPLE.pch"
	-@erase "$(INTDIR)\SIMPLE.res"
	-@erase "$(INTDIR)\SIMPLE.SBR"
	-@erase "$(INTDIR)\SIMPLEP.OBJ"
	-@erase "$(INTDIR)\SIMPLEP.SBR"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\SIMPLE.bsc"
	-@erase "$(OUTDIR)\simple.exp"
	-@erase "$(OUTDIR)\simple.ext"
	-@erase "$(OUTDIR)\simple.ilk"
	-@erase "$(OUTDIR)\simple.lib"
	-@erase "$(OUTDIR)\simple.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "__CV__" /D "STRICT" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /FR /Yu"simplep.hxx" /c
CPP_PROJ=/nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__CV__" /D "STRICT" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D\
 "__XTNSNDLL__" /FR"$(INTDIR)/" /Fp"$(INTDIR)/SIMPLE.pch" /Yu"simplep.hxx"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\WinDebug/
CPP_SBRS=.\WinDebug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/SIMPLE.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SIMPLE.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\SIMPLE.SBR" \
	"$(INTDIR)\SIMPLEP.SBR"

"$(OUTDIR)\SIMPLE.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 IxtAtd42.lib stdcppd.lib tfrm32d.lib cont32d.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /stub:"rights.exe" /out:"WinDebug/simple.ext"
LINK32_FLAGS=IxtAtd42.lib stdcppd.lib tfrm32d.lib cont32d.lib kernel32.lib\
 user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib\
 ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo\
 /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)/simple.pdb" /debug\
 /machine:I386 /def:".\SIMPLE.DEF" /stub:"rights.exe"\
 /out:"$(OUTDIR)/simple.ext" /implib:"$(OUTDIR)/simple.lib" 
DEF_FILE= \
	".\SIMPLE.DEF"
LINK32_OBJS= \
	"$(INTDIR)\SIMPLE.OBJ" \
	"$(INTDIR)\SIMPLE.res" \
	"$(INTDIR)\SIMPLEP.OBJ"

"$(OUTDIR)\simple.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "SIMPLE - Win32 Release"
# Name "SIMPLE - Win32 Debug"

!IF  "$(CFG)" == "SIMPLE - Win32 Release"

!ELSEIF  "$(CFG)" == "SIMPLE - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\SIMPLE.CXX
DEP_CPP_SIMPL=\
	".\simpguid.h"\
	".\SIMPLE.HXX"\
	".\SIMPLEP.HXX"\
	".\VERSION.H"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
	{$(INCLUDE)}"\cstddef"\
	{$(INCLUDE)}"\cstdio"\
	{$(INCLUDE)}"\cstdlib"\
	{$(INCLUDE)}"\cstring"\
	{$(INCLUDE)}"\cwchar"\
	{$(INCLUDE)}"\EIERUHR.HXX"\
	{$(INCLUDE)}"\eonrguid.h"\
	{$(INCLUDE)}"\ERRCODES.HXX"\
	{$(INCLUDE)}"\exception"\
	{$(INCLUDE)}"\ienumobj.hxx"\
	{$(INCLUDE)}"\ios"\
	{$(INCLUDE)}"\iosfwd"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\IXTENSN.HXX"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\stdexcept"\
	{$(INCLUDE)}"\streambuf"\
	{$(INCLUDE)}"\string"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\XTENSION.H"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\XTENSNX.H"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	

"$(INTDIR)\SIMPLE.OBJ" : $(SOURCE) $(DEP_CPP_SIMPL) "$(INTDIR)"\
 "$(INTDIR)\SIMPLE.pch"

"$(INTDIR)\SIMPLE.SBR" : $(SOURCE) $(DEP_CPP_SIMPL) "$(INTDIR)"\
 "$(INTDIR)\SIMPLE.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\SIMPLE.RC
DEP_RSC_SIMPLE=\
	".\SIMPLE.RCV"\
	

"$(INTDIR)\SIMPLE.res" : $(SOURCE) $(DEP_RSC_SIMPLE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\SIMPLEP.CXX
DEP_CPP_SIMPLEP=\
	".\SIMPLEP.HXX"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
	{$(INCLUDE)}"\cstddef"\
	{$(INCLUDE)}"\cstdio"\
	{$(INCLUDE)}"\cstdlib"\
	{$(INCLUDE)}"\cstring"\
	{$(INCLUDE)}"\cwchar"\
	{$(INCLUDE)}"\EIERUHR.HXX"\
	{$(INCLUDE)}"\eonrguid.h"\
	{$(INCLUDE)}"\ERRCODES.HXX"\
	{$(INCLUDE)}"\exception"\
	{$(INCLUDE)}"\ienumobj.hxx"\
	{$(INCLUDE)}"\ios"\
	{$(INCLUDE)}"\iosfwd"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\IXTENSN.HXX"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\stdexcept"\
	{$(INCLUDE)}"\streambuf"\
	{$(INCLUDE)}"\string"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\XTENSION.H"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\XTENSNX.H"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	

!IF  "$(CFG)" == "SIMPLE - Win32 Release"

# ADD CPP /Yc"simplep.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__CV__" /D "STRICT" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__"\
 /FR"$(INTDIR)/" /Fp"$(INTDIR)/SIMPLE.pch" /Yc"simplep.hxx" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\SIMPLEP.OBJ" : $(SOURCE) $(DEP_CPP_SIMPLEP) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\SIMPLEP.SBR" : $(SOURCE) $(DEP_CPP_SIMPLEP) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\SIMPLE.pch" : $(SOURCE) $(DEP_CPP_SIMPLEP) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "SIMPLE - Win32 Debug"

# ADD CPP /Yc"simplep.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__CV__" /D "STRICT" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D\
 "__XTNSNDLL__" /FR"$(INTDIR)/" /Fp"$(INTDIR)/SIMPLE.pch" /Yc"simplep.hxx"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\SIMPLEP.OBJ" : $(SOURCE) $(DEP_CPP_SIMPLEP) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\SIMPLEP.SBR" : $(SOURCE) $(DEP_CPP_SIMPLEP) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\SIMPLE.pch" : $(SOURCE) $(DEP_CPP_SIMPLEP) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SIMPLE.DEF

!IF  "$(CFG)" == "SIMPLE - Win32 Release"

!ELSEIF  "$(CFG)" == "SIMPLE - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
