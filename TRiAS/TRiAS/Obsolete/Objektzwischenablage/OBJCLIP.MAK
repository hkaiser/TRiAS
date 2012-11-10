# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=objclp32 - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to objclp32 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "objclp32 - Win32 Release" && "$(CFG)" !=\
 "objclp32 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "OBJCLIP.MAK" CFG="objclp32 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "objclp32 - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "objclp32 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "objclp32 - Win32 Debug"
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "objclp32 - Win32 Release"

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

ALL : "$(OUTDIR)\objclip.ext"

CLEAN : 
	-@erase "$(INTDIR)\OBJCLDLG.OBJ"
	-@erase "$(INTDIR)\OBJCLIP.OBJ"
	-@erase "$(INTDIR)\OBJCLIP.pch"
	-@erase "$(INTDIR)\OBJCLIPP.OBJ"
	-@erase "$(INTDIR)\objclp32.res"
	-@erase "$(INTDIR)\OBJMDLG.OBJ"
	-@erase "$(INTDIR)\OBJMLIST.OBJ"
	-@erase "$(INTDIR)\UNDOLIST.OBJ"
	-@erase "$(OUTDIR)\objclip.exp"
	-@erase "$(OUTDIR)\objclip.ext"
	-@erase "$(OUTDIR)\objclip.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/objclp32.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "__CV__" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTENSNDLL__" /D "STRICT" /D "DLL" /Yu"objclipp.hxx" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__CV__" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTENSNDLL__" /D "STRICT"\
 /D "DLL" /Fp"$(INTDIR)/OBJCLIP.pch" /Yu"objclipp.hxx" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /i ".." /d "NDEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/objclp32.res" /i ".." /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/OBJCLIP.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ixtnsr40.lib stdcppr.lib cont32r.lib tfrmwork.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /stub:"obj32/rights.exe" /out:"Release/objclip.ext" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=ixtnsr40.lib stdcppr.lib cont32r.lib tfrmwork.lib kernel32.lib\
 user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib\
 ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll\
 /incremental:no /pdb:"$(OUTDIR)/objclip.pdb" /machine:I386\
 /def:".\OBJ32\OBJCLP32.DEF" /stub:"obj32/rights.exe"\
 /out:"$(OUTDIR)/objclip.ext" /implib:"$(OUTDIR)/objclip.lib"\
 /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\OBJ32\OBJCLP32.DEF"
LINK32_OBJS= \
	"$(INTDIR)\OBJCLDLG.OBJ" \
	"$(INTDIR)\OBJCLIP.OBJ" \
	"$(INTDIR)\OBJCLIPP.OBJ" \
	"$(INTDIR)\objclp32.res" \
	"$(INTDIR)\OBJMDLG.OBJ" \
	"$(INTDIR)\OBJMLIST.OBJ" \
	"$(INTDIR)\UNDOLIST.OBJ"

"$(OUTDIR)\objclip.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "objclp32 - Win32 Debug"

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

ALL : "$(OUTDIR)\objclipd.ext" "$(OUTDIR)\OBJCLIP.bsc"

CLEAN : 
	-@erase "$(INTDIR)\OBJCLDLG.OBJ"
	-@erase "$(INTDIR)\OBJCLDLG.SBR"
	-@erase "$(INTDIR)\OBJCLIP.OBJ"
	-@erase "$(INTDIR)\OBJCLIP.SBR"
	-@erase "$(INTDIR)\objclipd.idb"
	-@erase "$(INTDIR)\objclipd.pch"
	-@erase "$(INTDIR)\objclipd.pdb"
	-@erase "$(INTDIR)\OBJCLIPP.OBJ"
	-@erase "$(INTDIR)\OBJCLIPP.SBR"
	-@erase "$(INTDIR)\objclp32.res"
	-@erase "$(INTDIR)\OBJMDLG.OBJ"
	-@erase "$(INTDIR)\OBJMDLG.SBR"
	-@erase "$(INTDIR)\OBJMLIST.OBJ"
	-@erase "$(INTDIR)\OBJMLIST.SBR"
	-@erase "$(INTDIR)\UNDOLIST.OBJ"
	-@erase "$(INTDIR)\UNDOLIST.SBR"
	-@erase "$(OUTDIR)\OBJCLIP.bsc"
	-@erase "$(OUTDIR)\objclipd.exp"
	-@erase "$(OUTDIR)\objclipd.ext"
	-@erase "$(OUTDIR)\objclipd.ilk"
	-@erase "$(OUTDIR)\objclipd.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/objclp32.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "__CV__" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTENSNDLL__" /D "STRICT" /D "DLL" /FR /Fp"Debug/objclipd.pch" /Yu"objclipp.hxx" /Fd"Debug/objclipd.pdb" /c
CPP_PROJ=/nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__CV__" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTENSNDLL__"\
 /D "STRICT" /D "DLL" /FR"$(INTDIR)/" /Fp"$(INTDIR)/objclipd.pch"\
 /Yu"objclipp.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/objclipd.pdb" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /i ".." /d "_DEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/objclp32.res" /i ".." /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/OBJCLIP.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\OBJCLDLG.SBR" \
	"$(INTDIR)\OBJCLIP.SBR" \
	"$(INTDIR)\OBJCLIPP.SBR" \
	"$(INTDIR)\OBJMDLG.SBR" \
	"$(INTDIR)\OBJMLIST.SBR" \
	"$(INTDIR)\UNDOLIST.SBR"

"$(OUTDIR)\OBJCLIP.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 ixtnsd40.lib stdcppd.lib cont32d.lib tfrm32d.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /stub:"obj32/rights.exe" /out:"Debug/objclipd.ext" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=ixtnsd40.lib stdcppd.lib cont32d.lib tfrm32d.lib kernel32.lib\
 user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib\
 ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll\
 /incremental:yes /pdb:"$(OUTDIR)/objclipd.pdb" /debug /machine:I386\
 /def:".\OBJ32\OBJCLP32.DEF" /stub:"obj32/rights.exe"\
 /out:"$(OUTDIR)/objclipd.ext" /implib:"$(OUTDIR)/objclipd.lib"\
 /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\OBJ32\OBJCLP32.DEF"
LINK32_OBJS= \
	"$(INTDIR)\OBJCLDLG.OBJ" \
	"$(INTDIR)\OBJCLIP.OBJ" \
	"$(INTDIR)\OBJCLIPP.OBJ" \
	"$(INTDIR)\objclp32.res" \
	"$(INTDIR)\OBJMDLG.OBJ" \
	"$(INTDIR)\OBJMLIST.OBJ" \
	"$(INTDIR)\UNDOLIST.OBJ"

"$(OUTDIR)\objclipd.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "objclp32 - Win32 Release"
# Name "objclp32 - Win32 Debug"

!IF  "$(CFG)" == "objclp32 - Win32 Release"

!ELSEIF  "$(CFG)" == "objclp32 - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\OBJCLIP.CXX

!IF  "$(CFG)" == "objclp32 - Win32 Release"

DEP_CPP_OBJCL=\
	".\objclip.h"\
	".\objclipp.hxx"\
	".\objclipr.h"\
	".\oclpguid.h"\
	".\version.h"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
	{$(INCLUDE)}"\cstddef"\
	{$(INCLUDE)}"\cstdio"\
	{$(INCLUDE)}"\cstdlib"\
	{$(INCLUDE)}"\cstring"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\exception"\
	{$(INCLUDE)}"\ios"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\stdexcept"\
	{$(INCLUDE)}"\streambuf"\
	{$(INCLUDE)}"\String"\
	{$(INCLUDE)}"\undoguid.h"\
	{$(INCLUDE)}"\use_ansi.h"\
	{$(INCLUDE)}"\utility"\
	{$(INCLUDE)}"\xiosbase"\
	{$(INCLUDE)}"\xlocale"\
	{$(INCLUDE)}"\xlocnum"\
	{$(INCLUDE)}"\xstddef"\
	{$(INCLUDE)}"\xstring"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	

"$(INTDIR)\OBJCLIP.OBJ" : $(SOURCE) $(DEP_CPP_OBJCL) "$(INTDIR)"\
 "$(INTDIR)\OBJCLIP.pch"


!ELSEIF  "$(CFG)" == "objclp32 - Win32 Debug"

DEP_CPP_OBJCL=\
	".\objcldlg.hxx"\
	".\objclip.h"\
	".\objclip.hxx"\
	".\objclipp.hxx"\
	".\objclipr.h"\
	".\oclpguid.h"\
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
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\Resstrg.h"\
	{$(INCLUDE)}"\stdexcept"\
	{$(INCLUDE)}"\streambuf"\
	{$(INCLUDE)}"\String"\
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
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	

"$(INTDIR)\OBJCLIP.OBJ" : $(SOURCE) $(DEP_CPP_OBJCL) "$(INTDIR)"\
 "$(INTDIR)\objclipd.pch"

"$(INTDIR)\OBJCLIP.SBR" : $(SOURCE) $(DEP_CPP_OBJCL) "$(INTDIR)"\
 "$(INTDIR)\objclipd.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OBJMDLG.CXX

!IF  "$(CFG)" == "objclp32 - Win32 Release"

DEP_CPP_OBJMD=\
	".\objcldlg.h"\
	".\objclipp.hxx"\
	".\objmdlg.hxx"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
	{$(INCLUDE)}"\cstddef"\
	{$(INCLUDE)}"\cstdio"\
	{$(INCLUDE)}"\cstdlib"\
	{$(INCLUDE)}"\cstring"\
	{$(INCLUDE)}"\exception"\
	{$(INCLUDE)}"\ios"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\stdexcept"\
	{$(INCLUDE)}"\streambuf"\
	{$(INCLUDE)}"\String"\
	{$(INCLUDE)}"\use_ansi.h"\
	{$(INCLUDE)}"\utility"\
	{$(INCLUDE)}"\xiosbase"\
	{$(INCLUDE)}"\xlocale"\
	{$(INCLUDE)}"\xlocnum"\
	{$(INCLUDE)}"\xstddef"\
	{$(INCLUDE)}"\xstring"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	

"$(INTDIR)\OBJMDLG.OBJ" : $(SOURCE) $(DEP_CPP_OBJMD) "$(INTDIR)"\
 "$(INTDIR)\OBJCLIP.pch"


!ELSEIF  "$(CFG)" == "objclp32 - Win32 Debug"

DEP_CPP_OBJMD=\
	".\objcldlg.h"\
	".\objcldlg.hxx"\
	".\objclip.hxx"\
	".\objclipp.hxx"\
	".\objmdlg.hxx"\
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
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\Resstrg.h"\
	{$(INCLUDE)}"\stdexcept"\
	{$(INCLUDE)}"\streambuf"\
	{$(INCLUDE)}"\String"\
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
	

"$(INTDIR)\OBJMDLG.OBJ" : $(SOURCE) $(DEP_CPP_OBJMD) "$(INTDIR)"\
 "$(INTDIR)\objclipd.pch"

"$(INTDIR)\OBJMDLG.SBR" : $(SOURCE) $(DEP_CPP_OBJMD) "$(INTDIR)"\
 "$(INTDIR)\objclipd.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OBJCLDLG.CXX

!IF  "$(CFG)" == "objclp32 - Win32 Release"

DEP_CPP_OBJCLD=\
	".\defabout.h"\
	".\defabout.hxx"\
	".\objcldlg.h"\
	".\objcldlg.hxx"\
	".\objclip.h"\
	".\objclipp.hxx"\
	".\objmdlg.hxx"\
	".\objmlist.hxx"\
	".\undolist.hxx"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
	{$(INCLUDE)}"\cstddef"\
	{$(INCLUDE)}"\cstdio"\
	{$(INCLUDE)}"\cstdlib"\
	{$(INCLUDE)}"\cstring"\
	{$(INCLUDE)}"\cwchar"\
	{$(INCLUDE)}"\Errinstx.hxx"\
	{$(INCLUDE)}"\exception"\
	{$(INCLUDE)}"\ios"\
	{$(INCLUDE)}"\iosfwd"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\stdexcept"\
	{$(INCLUDE)}"\streambuf"\
	{$(INCLUDE)}"\String"\
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
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	

"$(INTDIR)\OBJCLDLG.OBJ" : $(SOURCE) $(DEP_CPP_OBJCLD) "$(INTDIR)"\
 "$(INTDIR)\OBJCLIP.pch"


!ELSEIF  "$(CFG)" == "objclp32 - Win32 Debug"

DEP_CPP_OBJCLD=\
	".\defabout.h"\
	".\defabout.hxx"\
	".\objcldlg.h"\
	".\objcldlg.hxx"\
	".\objclip.h"\
	".\objclip.hxx"\
	".\objclipp.hxx"\
	".\objmdlg.hxx"\
	".\objmlist.hxx"\
	".\undolist.hxx"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
	{$(INCLUDE)}"\cstddef"\
	{$(INCLUDE)}"\cstdio"\
	{$(INCLUDE)}"\cstdlib"\
	{$(INCLUDE)}"\cstring"\
	{$(INCLUDE)}"\cwchar"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Errinstx.hxx"\
	{$(INCLUDE)}"\exception"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\ios"\
	{$(INCLUDE)}"\iosfwd"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\Resstrg.h"\
	{$(INCLUDE)}"\stdexcept"\
	{$(INCLUDE)}"\streambuf"\
	{$(INCLUDE)}"\String"\
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
	

"$(INTDIR)\OBJCLDLG.OBJ" : $(SOURCE) $(DEP_CPP_OBJCLD) "$(INTDIR)"\
 "$(INTDIR)\objclipd.pch"

"$(INTDIR)\OBJCLDLG.SBR" : $(SOURCE) $(DEP_CPP_OBJCLD) "$(INTDIR)"\
 "$(INTDIR)\objclipd.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\UNDOLIST.CXX

!IF  "$(CFG)" == "objclp32 - Win32 Release"

DEP_CPP_UNDOL=\
	".\objclipp.hxx"\
	".\objmlist.hxx"\
	".\undolist.hxx"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
	{$(INCLUDE)}"\cstddef"\
	{$(INCLUDE)}"\cstdio"\
	{$(INCLUDE)}"\cstdlib"\
	{$(INCLUDE)}"\cstring"\
	{$(INCLUDE)}"\exception"\
	{$(INCLUDE)}"\ios"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\stdexcept"\
	{$(INCLUDE)}"\streambuf"\
	{$(INCLUDE)}"\String"\
	{$(INCLUDE)}"\use_ansi.h"\
	{$(INCLUDE)}"\utility"\
	{$(INCLUDE)}"\xiosbase"\
	{$(INCLUDE)}"\xlocale"\
	{$(INCLUDE)}"\xlocnum"\
	{$(INCLUDE)}"\xstddef"\
	{$(INCLUDE)}"\xstring"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	

"$(INTDIR)\UNDOLIST.OBJ" : $(SOURCE) $(DEP_CPP_UNDOL) "$(INTDIR)"\
 "$(INTDIR)\OBJCLIP.pch"


!ELSEIF  "$(CFG)" == "objclp32 - Win32 Debug"

DEP_CPP_UNDOL=\
	".\objcldlg.hxx"\
	".\objclip.hxx"\
	".\objclipp.hxx"\
	".\objmlist.hxx"\
	".\undolist.hxx"\
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
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\Resstrg.h"\
	{$(INCLUDE)}"\stdexcept"\
	{$(INCLUDE)}"\streambuf"\
	{$(INCLUDE)}"\String"\
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
	

"$(INTDIR)\UNDOLIST.OBJ" : $(SOURCE) $(DEP_CPP_UNDOL) "$(INTDIR)"\
 "$(INTDIR)\objclipd.pch"

"$(INTDIR)\UNDOLIST.SBR" : $(SOURCE) $(DEP_CPP_UNDOL) "$(INTDIR)"\
 "$(INTDIR)\objclipd.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OBJMLIST.CXX

!IF  "$(CFG)" == "objclp32 - Win32 Release"

DEP_CPP_OBJML=\
	".\objclipp.hxx"\
	".\objmlist.hxx"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
	{$(INCLUDE)}"\cstddef"\
	{$(INCLUDE)}"\cstdio"\
	{$(INCLUDE)}"\cstdlib"\
	{$(INCLUDE)}"\cstring"\
	{$(INCLUDE)}"\exception"\
	{$(INCLUDE)}"\ios"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\stdexcept"\
	{$(INCLUDE)}"\streambuf"\
	{$(INCLUDE)}"\String"\
	{$(INCLUDE)}"\use_ansi.h"\
	{$(INCLUDE)}"\utility"\
	{$(INCLUDE)}"\xiosbase"\
	{$(INCLUDE)}"\xlocale"\
	{$(INCLUDE)}"\xlocnum"\
	{$(INCLUDE)}"\xstddef"\
	{$(INCLUDE)}"\xstring"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	

"$(INTDIR)\OBJMLIST.OBJ" : $(SOURCE) $(DEP_CPP_OBJML) "$(INTDIR)"\
 "$(INTDIR)\OBJCLIP.pch"


!ELSEIF  "$(CFG)" == "objclp32 - Win32 Debug"

DEP_CPP_OBJML=\
	".\objcldlg.hxx"\
	".\objclip.hxx"\
	".\objclipp.hxx"\
	".\objmlist.hxx"\
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
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\Resstrg.h"\
	{$(INCLUDE)}"\stdexcept"\
	{$(INCLUDE)}"\streambuf"\
	{$(INCLUDE)}"\String"\
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
	

"$(INTDIR)\OBJMLIST.OBJ" : $(SOURCE) $(DEP_CPP_OBJML) "$(INTDIR)"\
 "$(INTDIR)\objclipd.pch"

"$(INTDIR)\OBJMLIST.SBR" : $(SOURCE) $(DEP_CPP_OBJML) "$(INTDIR)"\
 "$(INTDIR)\objclipd.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OBJCLIPP.CXX

!IF  "$(CFG)" == "objclp32 - Win32 Release"

DEP_CPP_OBJCLI=\
	".\objclipp.hxx"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
	{$(INCLUDE)}"\cstddef"\
	{$(INCLUDE)}"\cstdio"\
	{$(INCLUDE)}"\cstdlib"\
	{$(INCLUDE)}"\cstring"\
	{$(INCLUDE)}"\exception"\
	{$(INCLUDE)}"\ios"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\stdexcept"\
	{$(INCLUDE)}"\streambuf"\
	{$(INCLUDE)}"\String"\
	{$(INCLUDE)}"\use_ansi.h"\
	{$(INCLUDE)}"\utility"\
	{$(INCLUDE)}"\xiosbase"\
	{$(INCLUDE)}"\xlocale"\
	{$(INCLUDE)}"\xlocnum"\
	{$(INCLUDE)}"\xstddef"\
	{$(INCLUDE)}"\xstring"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	
# ADD CPP /Yc"objclipp.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__CV__" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTENSNDLL__" /D "STRICT"\
 /D "DLL" /Fp"$(INTDIR)/OBJCLIP.pch" /Yc"objclipp.hxx" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\OBJCLIPP.OBJ" : $(SOURCE) $(DEP_CPP_OBJCLI) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\OBJCLIP.pch" : $(SOURCE) $(DEP_CPP_OBJCLI) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "objclp32 - Win32 Debug"

DEP_CPP_OBJCLI=\
	".\objcldlg.hxx"\
	".\objclip.hxx"\
	".\objclipp.hxx"\
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
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\Resstrg.h"\
	{$(INCLUDE)}"\stdexcept"\
	{$(INCLUDE)}"\streambuf"\
	{$(INCLUDE)}"\String"\
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
	
# ADD CPP /Yc"objclipp.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__CV__" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTENSNDLL__"\
 /D "STRICT" /D "DLL" /FR"$(INTDIR)/" /Fp"$(INTDIR)/objclipd.pch"\
 /Yc"objclipp.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/objclipd.pdb" /c $(SOURCE) \
	

"$(INTDIR)\OBJCLIPP.OBJ" : $(SOURCE) $(DEP_CPP_OBJCLI) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\OBJCLIPP.SBR" : $(SOURCE) $(DEP_CPP_OBJCLI) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\objclipd.pch" : $(SOURCE) $(DEP_CPP_OBJCLI) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OBJ32\objclp32.rc
DEP_RSC_OBJCLP=\
	".\OBJ32\defabout.src"\
	".\OBJ32\LUPE.ICO"\
	".\OBJ32\objclp32.rcv"\
	{$(INCLUDE)}"\Resstrg.h"\
	
NODEP_RSC_OBJCLP=\
	".\OBJ32\defabout.h"\
	".\OBJ32\objcldlg.h"\
	".\OBJ32\objclip.h"\
	

!IF  "$(CFG)" == "objclp32 - Win32 Release"


"$(INTDIR)\objclp32.res" : $(SOURCE) $(DEP_RSC_OBJCLP) "$(INTDIR)"
   $(RSC) /l 0x407 /fo"$(INTDIR)/objclp32.res" /i ".." /i "OBJ32" /d "NDEBUG"\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "objclp32 - Win32 Debug"


"$(INTDIR)\objclp32.res" : $(SOURCE) $(DEP_RSC_OBJCLP) "$(INTDIR)"
   $(RSC) /l 0x407 /fo"$(INTDIR)/objclp32.res" /i ".." /i "OBJ32" /d "_DEBUG"\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OBJ32\OBJCLP32.DEF

!IF  "$(CFG)" == "objclp32 - Win32 Release"

!ELSEIF  "$(CFG)" == "objclp32 - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
