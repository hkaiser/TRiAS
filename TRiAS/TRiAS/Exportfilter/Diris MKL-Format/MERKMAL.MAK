# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=merkm32 - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to merkm32 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "merkm32 - Win32 Release" && "$(CFG)" !=\
 "merkm32 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "MERKMAL.MAK" CFG="merkm32 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "merkm32 - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "merkm32 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "merkm32 - Win32 Debug"
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "merkm32 - Win32 Release"

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
TargetName=dirismkl
# End Custom Macros

ALL : "$(OUTDIR)\dirismkl.flt" "c:\trias.mvc\trias200.rel\dirismkl.ext"

CLEAN : 
	-@erase "$(INTDIR)\DIRISMKL.OBJ"
	-@erase "$(INTDIR)\DMKLCAP.OBJ"
	-@erase "$(INTDIR)\merkm32.res"
	-@erase "$(INTDIR)\MERKMAL.pch"
	-@erase "$(INTDIR)\MERKMP.OBJ"
	-@erase "$(OUTDIR)\dirismkl.exp"
	-@erase "$(OUTDIR)\dirismkl.flt"
	-@erase "$(OUTDIR)\dirismkl.lib"
	-@erase "c:\trias.mvc\trias200.rel\dirismkl.ext"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/merkm32.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /O2 /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__EXPFLTDLL__" /D "__XT" /Yu"merkmp.hxx" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /WX /GX /O2 /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D\
 "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__EXPFLTDLL__" /D "__XT"\
 /Fp"$(INTDIR)/MERKMAL.pch" /Yu"merkmp.hxx" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/merkm32.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/MERKMAL.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 tfrmwork.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /stub:"Obj32/rights.exe" /out:"Release/dirismkl.flt" /subsystem:windows,4.0
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=tfrmwork.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /dll /incremental:no\
 /pdb:"$(OUTDIR)/dirismkl.pdb" /machine:I386 /def:".\OBJ32\MERKM32.DEF"\
 /stub:"Obj32/rights.exe" /out:"$(OUTDIR)/dirismkl.flt"\
 /implib:"$(OUTDIR)/dirismkl.lib" /subsystem:windows,4.0 
DEF_FILE= \
	".\OBJ32\MERKM32.DEF"
LINK32_OBJS= \
	"$(INTDIR)\DIRISMKL.OBJ" \
	"$(INTDIR)\DMKLCAP.OBJ" \
	"$(INTDIR)\merkm32.res" \
	"$(INTDIR)\MERKMP.OBJ"

"$(OUTDIR)\dirismkl.flt" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
TargetPath=.\Release\dirismkl.flt
TargetName=dirismkl
InputPath=.\Release\dirismkl.flt
SOURCE=$(InputPath)

"c:\trias.mvc\trias200.rel\$(TargetName).ext" : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
   copy "$(TargetPath)" c:\trias.mvc\trias200.rel

# End Custom Build

!ELSEIF  "$(CFG)" == "merkm32 - Win32 Debug"

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
TargetName=dirismkl
# End Custom Macros

ALL : "$(OUTDIR)\dirismkl.flt" "c:\trias.mvc\trias200\dirismkl.ext"

CLEAN : 
	-@erase "$(INTDIR)\DIRISMKL.OBJ"
	-@erase "$(INTDIR)\DMKLCAP.OBJ"
	-@erase "$(INTDIR)\merkm32.res"
	-@erase "$(INTDIR)\MERKMAL.pch"
	-@erase "$(INTDIR)\MERKMP.OBJ"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\dirismkl.exp"
	-@erase "$(OUTDIR)\dirismkl.flt"
	-@erase "$(OUTDIR)\dirismkl.ilk"
	-@erase "$(OUTDIR)\dirismkl.lib"
	-@erase "$(OUTDIR)\dirismkl.pdb"
	-@erase "c:\trias.mvc\trias200\dirismkl.ext"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/merkm32.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__EXPFLTDLL__" /D "__XT" /Yu"merkmp.hxx" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__EXPFLTDLL__" /D\
 "__XT" /Fp"$(INTDIR)/MERKMAL.pch" /Yu"merkmp.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/merkm32.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/MERKMAL.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 tfrm32d.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /stub:"Obj32/rights.exe" /out:"Debug/dirismkl.flt" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=tfrm32d.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /dll /incremental:yes\
 /pdb:"$(OUTDIR)/dirismkl.pdb" /debug /machine:I386 /def:".\OBJ32\MERKM32.DEF"\
 /stub:"Obj32/rights.exe" /out:"$(OUTDIR)/dirismkl.flt"\
 /implib:"$(OUTDIR)/dirismkl.lib" /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\OBJ32\MERKM32.DEF"
LINK32_OBJS= \
	"$(INTDIR)\DIRISMKL.OBJ" \
	"$(INTDIR)\DMKLCAP.OBJ" \
	"$(INTDIR)\merkm32.res" \
	"$(INTDIR)\MERKMP.OBJ"

"$(OUTDIR)\dirismkl.flt" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
TargetPath=.\Debug\dirismkl.flt
TargetName=dirismkl
InputPath=.\Debug\dirismkl.flt
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

# Name "merkm32 - Win32 Release"
# Name "merkm32 - Win32 Debug"

!IF  "$(CFG)" == "merkm32 - Win32 Release"

!ELSEIF  "$(CFG)" == "merkm32 - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\DMKLCAP.CXX

!IF  "$(CFG)" == "merkm32 - Win32 Release"

DEP_CPP_DMKLC=\
	".\MERKMP.HXX"\
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
	

"$(INTDIR)\DMKLCAP.OBJ" : $(SOURCE) $(DEP_CPP_DMKLC) "$(INTDIR)"\
 "$(INTDIR)\MERKMAL.pch"


!ELSEIF  "$(CFG)" == "merkm32 - Win32 Debug"

DEP_CPP_DMKLC=\
	".\MERKMP.HXX"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCNUM"\
	

"$(INTDIR)\DMKLCAP.OBJ" : $(SOURCE) $(DEP_CPP_DMKLC) "$(INTDIR)"\
 "$(INTDIR)\MERKMAL.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DIRISMKL.CXX

!IF  "$(CFG)" == "merkm32 - Win32 Release"

DEP_CPP_DIRIS=\
	".\DIRISMKL.HXX"\
	".\MERKMP.HXX"\
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
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

"$(INTDIR)\DIRISMKL.OBJ" : $(SOURCE) $(DEP_CPP_DIRIS) "$(INTDIR)"\
 "$(INTDIR)\MERKMAL.pch"


!ELSEIF  "$(CFG)" == "merkm32 - Win32 Debug"

DEP_CPP_DIRIS=\
	".\DIRISMKL.HXX"\
	".\MERKMP.HXX"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

"$(INTDIR)\DIRISMKL.OBJ" : $(SOURCE) $(DEP_CPP_DIRIS) "$(INTDIR)"\
 "$(INTDIR)\MERKMAL.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MERKMP.CXX

!IF  "$(CFG)" == "merkm32 - Win32 Release"

DEP_CPP_MERKM=\
	".\MERKMP.HXX"\
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
	
# ADD CPP /Yc"merkmp.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O2 /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D\
 "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__EXPFLTDLL__" /D "__XT"\
 /Fp"$(INTDIR)/MERKMAL.pch" /Yc"merkmp.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\MERKMP.OBJ" : $(SOURCE) $(DEP_CPP_MERKM) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\MERKMAL.pch" : $(SOURCE) $(DEP_CPP_MERKM) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "merkm32 - Win32 Debug"

DEP_CPP_MERKM=\
	".\MERKMP.HXX"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCNUM"\
	
# ADD CPP /WX /Yc"merkmp.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__EXPFLTDLL__" /D\
 "__XT" /Fp"$(INTDIR)/MERKMAL.pch" /Yc"merkmp.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\MERKMP.OBJ" : $(SOURCE) $(DEP_CPP_MERKM) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\MERKMAL.pch" : $(SOURCE) $(DEP_CPP_MERKM) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OBJ32\MERKM32.DEF

!IF  "$(CFG)" == "merkm32 - Win32 Release"

!ELSEIF  "$(CFG)" == "merkm32 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OBJ32\merkm32.rc
DEP_RSC_MERKM3=\
	".\OBJ32\merkm32.rcv"\
	

!IF  "$(CFG)" == "merkm32 - Win32 Release"


"$(INTDIR)\merkm32.res" : $(SOURCE) $(DEP_RSC_MERKM3) "$(INTDIR)"
   $(RSC) /l 0x407 /fo"$(INTDIR)/merkm32.res" /i "OBJ32" /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "merkm32 - Win32 Debug"


"$(INTDIR)\merkm32.res" : $(SOURCE) $(DEP_RSC_MERKM3) "$(INTDIR)"
   $(RSC) /l 0x407 /fo"$(INTDIR)/merkm32.res" /i "OBJ32" /d "_DEBUG" $(SOURCE)


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
