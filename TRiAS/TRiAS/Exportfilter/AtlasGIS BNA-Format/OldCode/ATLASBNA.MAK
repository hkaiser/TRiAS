# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=atlas32 - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to atlas32 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "atlas32 - Win32 Release" && "$(CFG)" !=\
 "atlas32 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "ATLASBNA.MAK" CFG="atlas32 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "atlas32 - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "atlas32 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "atlas32 - Win32 Debug"
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "atlas32 - Win32 Release"

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
TargetName=atlasbna
# End Custom Macros

ALL : "$(OUTDIR)\atlasbna.flt" "c:\trias.mvc\trias200.rel\atlasbna.ext"

CLEAN : 
	-@erase "$(INTDIR)\atlas32.res"
	-@erase "$(INTDIR)\ATLASBNA.pch"
	-@erase "$(INTDIR)\ATLASCAP.OBJ"
	-@erase "$(INTDIR)\ATLASEXP.OBJ"
	-@erase "$(INTDIR)\ATLASP.OBJ"
	-@erase "$(INTDIR)\STRUTIL.OBJ"
	-@erase "$(OUTDIR)\atlasbna.exp"
	-@erase "$(OUTDIR)\atlasbna.flt"
	-@erase "$(OUTDIR)\atlasbna.lib"
	-@erase "c:\trias.mvc\trias200.rel\atlasbna.ext"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/atlas32.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "__XT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__EXPFLTDLL__" /Yu"atlasp.hxx" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "__XT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__EXPFLTDLL__"\
 /Fp"$(INTDIR)/ATLASBNA.pch" /Yu"atlasp.hxx" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/atlas32.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/ATLASBNA.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 tfrmwork.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /stub:"obj32\rights.exe" /out:"Release/atlasbna.flt" /subsystem:windows,4.0
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=tfrmwork.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /dll /incremental:no\
 /pdb:"$(OUTDIR)/atlasbna.pdb" /machine:I386 /def:".\OBJ32\ATLAS32.DEF"\
 /stub:"obj32\rights.exe" /out:"$(OUTDIR)/atlasbna.flt"\
 /implib:"$(OUTDIR)/atlasbna.lib" /subsystem:windows,4.0 
DEF_FILE= \
	".\OBJ32\ATLAS32.DEF"
LINK32_OBJS= \
	"$(INTDIR)\atlas32.res" \
	"$(INTDIR)\ATLASCAP.OBJ" \
	"$(INTDIR)\ATLASEXP.OBJ" \
	"$(INTDIR)\ATLASP.OBJ" \
	"$(INTDIR)\STRUTIL.OBJ"

"$(OUTDIR)\atlasbna.flt" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
TargetPath=.\Release\atlasbna.flt
TargetName=atlasbna
InputPath=.\Release\atlasbna.flt
SOURCE=$(InputPath)

"c:\trias.mvc\trias200.rel\$(TargetName).ext" : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
   copy "$(TargetPath)" c:\trias.mvc\trias200.rel

# End Custom Build

!ELSEIF  "$(CFG)" == "atlas32 - Win32 Debug"

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
TargetName=atlasbna
# End Custom Macros

ALL : "$(OUTDIR)\atlasbna.flt" "c:\trias.mvc\trias200\atlasbna.ext"

CLEAN : 
	-@erase "$(INTDIR)\atlas32.res"
	-@erase "$(INTDIR)\ATLASBNA.pch"
	-@erase "$(INTDIR)\ATLASCAP.OBJ"
	-@erase "$(INTDIR)\ATLASEXP.OBJ"
	-@erase "$(INTDIR)\ATLASP.OBJ"
	-@erase "$(INTDIR)\STRUTIL.OBJ"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\atlasbna.exp"
	-@erase "$(OUTDIR)\atlasbna.flt"
	-@erase "$(OUTDIR)\atlasbna.ilk"
	-@erase "$(OUTDIR)\atlasbna.lib"
	-@erase "$(OUTDIR)\atlasbna.pdb"
	-@erase "c:\trias.mvc\trias200\atlasbna.ext"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/atlas32.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "__XT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__EXPFLTDLL__" /Yu"atlasp.hxx" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "__XT" /D "DLL" /D "MSWIND" /D "__CV__" /D\
 "__EXPFLTDLL__" /Fp"$(INTDIR)/ATLASBNA.pch" /Yu"atlasp.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/atlas32.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/ATLASBNA.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 tfrm32d.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /stub:"obj32\rights.exe" /out:"Debug/atlasbna.flt" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=tfrm32d.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /dll /incremental:yes\
 /pdb:"$(OUTDIR)/atlasbna.pdb" /debug /machine:I386 /def:".\OBJ32\ATLAS32.DEF"\
 /stub:"obj32\rights.exe" /out:"$(OUTDIR)/atlasbna.flt"\
 /implib:"$(OUTDIR)/atlasbna.lib" /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\OBJ32\ATLAS32.DEF"
LINK32_OBJS= \
	"$(INTDIR)\atlas32.res" \
	"$(INTDIR)\ATLASCAP.OBJ" \
	"$(INTDIR)\ATLASEXP.OBJ" \
	"$(INTDIR)\ATLASP.OBJ" \
	"$(INTDIR)\STRUTIL.OBJ"

"$(OUTDIR)\atlasbna.flt" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
TargetPath=.\Debug\atlasbna.flt
TargetName=atlasbna
InputPath=.\Debug\atlasbna.flt
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

# Name "atlas32 - Win32 Release"
# Name "atlas32 - Win32 Debug"

!IF  "$(CFG)" == "atlas32 - Win32 Release"

!ELSEIF  "$(CFG)" == "atlas32 - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ATLASCAP.CXX

!IF  "$(CFG)" == "atlas32 - Win32 Release"

DEP_CPP_ATLAS=\
	".\ATLASP.HXX"\
	{$(INCLUDE)}"\Attribs.hxx"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\Impexp.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\ATLASCAP.OBJ" : $(SOURCE) $(DEP_CPP_ATLAS) "$(INTDIR)"\
 "$(INTDIR)\ATLASBNA.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "__XT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__EXPFLTDLL__"\
 /Fp"$(INTDIR)/ATLASBNA.pch" /Yu"atlasp.hxx" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "atlas32 - Win32 Debug"

DEP_CPP_ATLAS=\
	".\ATLASP.HXX"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	
# ADD CPP /Yu"atlasp.hxx"

"$(INTDIR)\ATLASCAP.OBJ" : $(SOURCE) $(DEP_CPP_ATLAS) "$(INTDIR)"\
 "$(INTDIR)\ATLASBNA.pch"
   $(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "__XT" /D "DLL" /D "MSWIND" /D "__CV__" /D\
 "__EXPFLTDLL__" /Fp"$(INTDIR)/ATLASBNA.pch" /Yu"atlasp.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ATLASEXP.CXX

!IF  "$(CFG)" == "atlas32 - Win32 Release"

DEP_CPP_ATLASE=\
	".\ATLASEXP.HXX"\
	".\ATLASP.HXX"\
	{$(INCLUDE)}"\Attribs.hxx"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\Impexp.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
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
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

"$(INTDIR)\ATLASEXP.OBJ" : $(SOURCE) $(DEP_CPP_ATLASE) "$(INTDIR)"\
 "$(INTDIR)\ATLASBNA.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "__XT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__EXPFLTDLL__"\
 /Fp"$(INTDIR)/ATLASBNA.pch" /Yu"atlasp.hxx" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "atlas32 - Win32 Debug"

DEP_CPP_ATLASE=\
	".\ATLASEXP.HXX"\
	".\ATLASP.HXX"\
	{$(INCLUDE)}"\Attribs.hxx"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\Impexp.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
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
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	
# ADD CPP /Yu"atlasp.hxx"

"$(INTDIR)\ATLASEXP.OBJ" : $(SOURCE) $(DEP_CPP_ATLASE) "$(INTDIR)"\
 "$(INTDIR)\ATLASBNA.pch"
   $(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "__XT" /D "DLL" /D "MSWIND" /D "__CV__" /D\
 "__EXPFLTDLL__" /Fp"$(INTDIR)/ATLASBNA.pch" /Yu"atlasp.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRUTIL.CXX

!IF  "$(CFG)" == "atlas32 - Win32 Release"

DEP_CPP_STRUT=\
	".\ATLASP.HXX"\
	{$(INCLUDE)}"\Attribs.hxx"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\Impexp.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\STRUTIL.OBJ" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"\
 "$(INTDIR)\ATLASBNA.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "__XT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__EXPFLTDLL__"\
 /Fp"$(INTDIR)/ATLASBNA.pch" /Yu"atlasp.hxx" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "atlas32 - Win32 Debug"

DEP_CPP_STRUT=\
	".\ATLASP.HXX"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	
# ADD CPP /Yu"atlasp.hxx"

"$(INTDIR)\STRUTIL.OBJ" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"\
 "$(INTDIR)\ATLASBNA.pch"
   $(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "__XT" /D "DLL" /D "MSWIND" /D "__CV__" /D\
 "__EXPFLTDLL__" /Fp"$(INTDIR)/ATLASBNA.pch" /Yu"atlasp.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ATLASP.CXX

!IF  "$(CFG)" == "atlas32 - Win32 Release"

DEP_CPP_ATLASP=\
	".\ATLASP.HXX"\
	{$(INCLUDE)}"\Attribs.hxx"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\Impexp.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	
# ADD CPP /Yc"atlasp.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "__XT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__EXPFLTDLL__"\
 /Fp"$(INTDIR)/ATLASBNA.pch" /Yc"atlasp.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\ATLASP.OBJ" : $(SOURCE) $(DEP_CPP_ATLASP) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\ATLASBNA.pch" : $(SOURCE) $(DEP_CPP_ATLASP) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "atlas32 - Win32 Debug"

DEP_CPP_ATLASP=\
	".\ATLASP.HXX"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	
# ADD CPP /Yc

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "__XT" /D "DLL" /D "MSWIND" /D "__CV__" /D\
 "__EXPFLTDLL__" /Fp"$(INTDIR)/ATLASBNA.pch" /Yc /Fo"$(INTDIR)/" /Fd"$(INTDIR)/"\
 /c $(SOURCE) \
	

"$(INTDIR)\ATLASP.OBJ" : $(SOURCE) $(DEP_CPP_ATLASP) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\ATLASBNA.pch" : $(SOURCE) $(DEP_CPP_ATLASP) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OBJ32\ATLAS32.DEF

!IF  "$(CFG)" == "atlas32 - Win32 Release"

!ELSEIF  "$(CFG)" == "atlas32 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OBJ32\atlas32.rc
DEP_RSC_ATLAS3=\
	".\OBJ32\atlas32.rcv"\
	

!IF  "$(CFG)" == "atlas32 - Win32 Release"


"$(INTDIR)\atlas32.res" : $(SOURCE) $(DEP_RSC_ATLAS3) "$(INTDIR)"
   $(RSC) /l 0x407 /fo"$(INTDIR)/atlas32.res" /i "OBJ32" /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "atlas32 - Win32 Debug"


"$(INTDIR)\atlas32.res" : $(SOURCE) $(DEP_RSC_ATLAS3) "$(INTDIR)"
   $(RSC) /l 0x407 /fo"$(INTDIR)/atlas32.res" /i "OBJ32" /d "_DEBUG" $(SOURCE)


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
