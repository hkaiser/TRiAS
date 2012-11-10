# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

!IF "$(CFG)" == ""
CFG=bsl - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to bsl - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "bsl - Win32 Release" && "$(CFG)" != "bsl - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "bsl.mak" CFG="bsl - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "bsl - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "bsl - Win32 Debug" (based on "Win32 (x86) Console Application")
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
# PROP Target_Last_Scanned "bsl - Win32 Debug"
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "bsl - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\bsl.exe"

CLEAN : 
	-@erase "$(INTDIR)\Bsl.obj"
	-@erase "$(INTDIR)\bsl.pch"
	-@erase "$(INTDIR)\Bsl.res"
	-@erase "$(INTDIR)\BslApp.obj"
	-@erase "$(INTDIR)\Bslp.obj"
	-@erase "$(INTDIR)\DoWork.obj"
	-@erase "$(INTDIR)\ExtList.obj"
	-@erase "$(INTDIR)\FNameStr.obj"
	-@erase "$(INTDIR)\Usage.obj"
	-@erase "$(OUTDIR)\bsl.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "EBWIN32" /D "OS_WIN_95" /D "OS_NO_ALLOCATORS" /D "OS_ALTERNATE_STRING_NAMES" /Yu"Bslp.h" /c
CPP_PROJ=/nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D\
 "EBWIN32" /D "OS_WIN_95" /D "OS_NO_ALLOCATORS" /D "OS_ALTERNATE_STRING_NAMES"\
 /Fp"$(INTDIR)/bsl.pch" /Yu"Bslp.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/Bsl.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/bsl.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 ebn.lib ospace2r.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
LINK32_FLAGS=ebn.lib ospace2r.lib kernel32.lib user32.lib gdi32.lib\
 winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib\
 uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)/bsl.pdb" /machine:I386 /def:".\bcl.def"\
 /out:"$(OUTDIR)/bsl.exe" 
DEF_FILE= \
	".\bcl.def"
LINK32_OBJS= \
	"$(INTDIR)\Bsl.obj" \
	"$(INTDIR)\Bsl.res" \
	"$(INTDIR)\BslApp.obj" \
	"$(INTDIR)\Bslp.obj" \
	"$(INTDIR)\DoWork.obj" \
	"$(INTDIR)\ExtList.obj" \
	"$(INTDIR)\FNameStr.obj" \
	"$(INTDIR)\Usage.obj"

"$(OUTDIR)\bsl.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "bsl - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
ProjDir=.
TargetName=bsld
# End Custom Macros

ALL : "$(OUTDIR)\bsld.exe" "$(OUTDIR)\bsl.bsc" ".\Data\bsld.exe"

CLEAN : 
	-@erase "$(INTDIR)\Bsl.obj"
	-@erase "$(INTDIR)\bsl.pch"
	-@erase "$(INTDIR)\Bsl.res"
	-@erase "$(INTDIR)\Bsl.sbr"
	-@erase "$(INTDIR)\BslApp.obj"
	-@erase "$(INTDIR)\BslApp.sbr"
	-@erase "$(INTDIR)\Bslp.obj"
	-@erase "$(INTDIR)\Bslp.sbr"
	-@erase "$(INTDIR)\DoWork.obj"
	-@erase "$(INTDIR)\DoWork.sbr"
	-@erase "$(INTDIR)\ExtList.obj"
	-@erase "$(INTDIR)\ExtList.sbr"
	-@erase "$(INTDIR)\FNameStr.obj"
	-@erase "$(INTDIR)\FNameStr.sbr"
	-@erase "$(INTDIR)\Usage.obj"
	-@erase "$(INTDIR)\Usage.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\bsl.bsc"
	-@erase "$(OUTDIR)\bsld.exe"
	-@erase "$(OUTDIR)\bsld.ilk"
	-@erase "$(OUTDIR)\bsld.pdb"
	-@erase ".\Data\bsld.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "EBWIN32" /D "OS_WIN_95" /D "OS_NO_ALLOCATORS" /D "OS_ALTERNATE_STRING_NAMES" /FR /Yu"Bslp.h" /c
CPP_PROJ=/nologo /MDd /W3 /WX /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D\
 "_CONSOLE" /D "EBWIN32" /D "OS_WIN_95" /D "OS_NO_ALLOCATORS" /D\
 "OS_ALTERNATE_STRING_NAMES" /FR"$(INTDIR)/" /Fp"$(INTDIR)/bsl.pch" /Yu"Bslp.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/Bsl.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/bsl.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Bsl.sbr" \
	"$(INTDIR)\BslApp.sbr" \
	"$(INTDIR)\Bslp.sbr" \
	"$(INTDIR)\DoWork.sbr" \
	"$(INTDIR)\ExtList.sbr" \
	"$(INTDIR)\FNameStr.sbr" \
	"$(INTDIR)\Usage.sbr"

"$(OUTDIR)\bsl.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 ebn.lib ospace2d.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /out:"Debug/bsld.exe"
LINK32_FLAGS=ebn.lib ospace2d.lib kernel32.lib user32.lib gdi32.lib\
 winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib\
 uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)/bsld.pdb" /debug /machine:I386 /def:".\bcl.def"\
 /out:"$(OUTDIR)/bsld.exe" 
DEF_FILE= \
	".\bcl.def"
LINK32_OBJS= \
	"$(INTDIR)\Bsl.obj" \
	"$(INTDIR)\Bsl.res" \
	"$(INTDIR)\BslApp.obj" \
	"$(INTDIR)\Bslp.obj" \
	"$(INTDIR)\DoWork.obj" \
	"$(INTDIR)\ExtList.obj" \
	"$(INTDIR)\FNameStr.obj" \
	"$(INTDIR)\Usage.obj"

"$(OUTDIR)\bsld.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
ProjDir=.
TargetPath=.\Debug\bsld.exe
TargetName=bsld
InputPath=.\Debug\bsld.exe
SOURCE=$(InputPath)

"$(ProjDir)\Data\$(TargetName).exe." : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   copy $(TargetPath) $(ProjDir)\Data

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

# Name "bsl - Win32 Release"
# Name "bsl - Win32 Debug"

!IF  "$(CFG)" == "bsl - Win32 Release"

!ELSEIF  "$(CFG)" == "bsl - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Bsl.cpp
DEP_CPP_BSL_C=\
	".\BclError.h"\
	".\bslapp.h"\
	".\bslp.h"\
	".\ExtList.h"\
	".\fnamestr.h"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cstddef"\
	{$(INCLUDE)}"\cstdio"\
	{$(INCLUDE)}"\cstdlib"\
	{$(INCLUDE)}"\cstring"\
	{$(INCLUDE)}"\cwchar"\
	{$(INCLUDE)}"\exception"\
	{$(INCLUDE)}"\functional"\
	{$(INCLUDE)}"\ios"\
	{$(INCLUDE)}"\iosfwd"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\iterator"\
	{$(INCLUDE)}"\list"\
	{$(INCLUDE)}"\map"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
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
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
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
	{$(INCLUDE)}"\xtree"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	

!IF  "$(CFG)" == "bsl - Win32 Release"


"$(INTDIR)\Bsl.obj" : $(SOURCE) $(DEP_CPP_BSL_C) "$(INTDIR)"\
 "$(INTDIR)\bsl.pch"


!ELSEIF  "$(CFG)" == "bsl - Win32 Debug"


"$(INTDIR)\Bsl.obj" : $(SOURCE) $(DEP_CPP_BSL_C) "$(INTDIR)"\
 "$(INTDIR)\bsl.pch"

"$(INTDIR)\Bsl.sbr" : $(SOURCE) $(DEP_CPP_BSL_C) "$(INTDIR)"\
 "$(INTDIR)\bsl.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Bslp.cpp
DEP_CPP_BSLP_=\
	".\BclError.h"\
	".\bslp.h"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cstddef"\
	{$(INCLUDE)}"\cstdio"\
	{$(INCLUDE)}"\cstdlib"\
	{$(INCLUDE)}"\cstring"\
	{$(INCLUDE)}"\cwchar"\
	{$(INCLUDE)}"\exception"\
	{$(INCLUDE)}"\functional"\
	{$(INCLUDE)}"\ios"\
	{$(INCLUDE)}"\iosfwd"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\iterator"\
	{$(INCLUDE)}"\list"\
	{$(INCLUDE)}"\map"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
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
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
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
	{$(INCLUDE)}"\xtree"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	

!IF  "$(CFG)" == "bsl - Win32 Release"

# ADD CPP /Yc"Bslp.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D\
 "EBWIN32" /D "OS_WIN_95" /D "OS_NO_ALLOCATORS" /D "OS_ALTERNATE_STRING_NAMES"\
 /Fp"$(INTDIR)/bsl.pch" /Yc"Bslp.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\Bslp.obj" : $(SOURCE) $(DEP_CPP_BSLP_) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\bsl.pch" : $(SOURCE) $(DEP_CPP_BSLP_) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "bsl - Win32 Debug"

# ADD CPP /Yc"Bslp.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D\
 "_CONSOLE" /D "EBWIN32" /D "OS_WIN_95" /D "OS_NO_ALLOCATORS" /D\
 "OS_ALTERNATE_STRING_NAMES" /FR"$(INTDIR)/" /Fp"$(INTDIR)/bsl.pch" /Yc"Bslp.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\Bslp.obj" : $(SOURCE) $(DEP_CPP_BSLP_) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Bslp.sbr" : $(SOURCE) $(DEP_CPP_BSLP_) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\bsl.pch" : $(SOURCE) $(DEP_CPP_BSLP_) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Usage.cpp
DEP_CPP_USAGE=\
	".\BclError.h"\
	".\bslapp.h"\
	".\bslp.h"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cstddef"\
	{$(INCLUDE)}"\cstdio"\
	{$(INCLUDE)}"\cstdlib"\
	{$(INCLUDE)}"\cstring"\
	{$(INCLUDE)}"\cwchar"\
	{$(INCLUDE)}"\exception"\
	{$(INCLUDE)}"\functional"\
	{$(INCLUDE)}"\ios"\
	{$(INCLUDE)}"\iosfwd"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\iterator"\
	{$(INCLUDE)}"\list"\
	{$(INCLUDE)}"\map"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
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
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
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
	{$(INCLUDE)}"\xtree"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	

!IF  "$(CFG)" == "bsl - Win32 Release"


"$(INTDIR)\Usage.obj" : $(SOURCE) $(DEP_CPP_USAGE) "$(INTDIR)"\
 "$(INTDIR)\bsl.pch"


!ELSEIF  "$(CFG)" == "bsl - Win32 Debug"


"$(INTDIR)\Usage.obj" : $(SOURCE) $(DEP_CPP_USAGE) "$(INTDIR)"\
 "$(INTDIR)\bsl.pch"

"$(INTDIR)\Usage.sbr" : $(SOURCE) $(DEP_CPP_USAGE) "$(INTDIR)"\
 "$(INTDIR)\bsl.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Bsl.rc
DEP_RSC_BSL_R=\
	".\res\bsl.rcv"\
	".\res\copystr.rc"\
	

"$(INTDIR)\Bsl.res" : $(SOURCE) $(DEP_RSC_BSL_R) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DoWork.cpp
DEP_CPP_DOWOR=\
	".\BclError.h"\
	".\bslapp.h"\
	".\bslp.h"\
	".\fnamestr.h"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cstddef"\
	{$(INCLUDE)}"\cstdio"\
	{$(INCLUDE)}"\cstdlib"\
	{$(INCLUDE)}"\cstring"\
	{$(INCLUDE)}"\cwchar"\
	{$(INCLUDE)}"\exception"\
	{$(INCLUDE)}"\functional"\
	{$(INCLUDE)}"\ios"\
	{$(INCLUDE)}"\iosfwd"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\iterator"\
	{$(INCLUDE)}"\list"\
	{$(INCLUDE)}"\map"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
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
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
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
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\stdexcept"\
	{$(INCLUDE)}"\streambuf"\
	{$(INCLUDE)}"\string"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
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
	{$(INCLUDE)}"\xtree"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	

!IF  "$(CFG)" == "bsl - Win32 Release"


"$(INTDIR)\DoWork.obj" : $(SOURCE) $(DEP_CPP_DOWOR) "$(INTDIR)"\
 "$(INTDIR)\bsl.pch"


!ELSEIF  "$(CFG)" == "bsl - Win32 Debug"


"$(INTDIR)\DoWork.obj" : $(SOURCE) $(DEP_CPP_DOWOR) "$(INTDIR)"\
 "$(INTDIR)\bsl.pch"

"$(INTDIR)\DoWork.sbr" : $(SOURCE) $(DEP_CPP_DOWOR) "$(INTDIR)"\
 "$(INTDIR)\bsl.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\bcl.def

!IF  "$(CFG)" == "bsl - Win32 Release"

!ELSEIF  "$(CFG)" == "bsl - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ExtList.cpp
DEP_CPP_EXTLI=\
	".\BclError.h"\
	".\bslp.h"\
	".\ExtList.h"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cstddef"\
	{$(INCLUDE)}"\cstdio"\
	{$(INCLUDE)}"\cstdlib"\
	{$(INCLUDE)}"\cstring"\
	{$(INCLUDE)}"\cwchar"\
	{$(INCLUDE)}"\exception"\
	{$(INCLUDE)}"\functional"\
	{$(INCLUDE)}"\ios"\
	{$(INCLUDE)}"\iosfwd"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\iterator"\
	{$(INCLUDE)}"\list"\
	{$(INCLUDE)}"\map"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
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
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
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
	{$(INCLUDE)}"\xtree"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	

!IF  "$(CFG)" == "bsl - Win32 Release"


"$(INTDIR)\ExtList.obj" : $(SOURCE) $(DEP_CPP_EXTLI) "$(INTDIR)"\
 "$(INTDIR)\bsl.pch"


!ELSEIF  "$(CFG)" == "bsl - Win32 Debug"


"$(INTDIR)\ExtList.obj" : $(SOURCE) $(DEP_CPP_EXTLI) "$(INTDIR)"\
 "$(INTDIR)\bsl.pch"

"$(INTDIR)\ExtList.sbr" : $(SOURCE) $(DEP_CPP_EXTLI) "$(INTDIR)"\
 "$(INTDIR)\bsl.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FNameStr.cpp
DEP_CPP_FNAME=\
	".\BclError.h"\
	".\bslp.h"\
	".\fnamestr.h"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cstddef"\
	{$(INCLUDE)}"\cstdio"\
	{$(INCLUDE)}"\cstdlib"\
	{$(INCLUDE)}"\cstring"\
	{$(INCLUDE)}"\cwchar"\
	{$(INCLUDE)}"\exception"\
	{$(INCLUDE)}"\functional"\
	{$(INCLUDE)}"\ios"\
	{$(INCLUDE)}"\iosfwd"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\iterator"\
	{$(INCLUDE)}"\list"\
	{$(INCLUDE)}"\map"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
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
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
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
	{$(INCLUDE)}"\xtree"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	

!IF  "$(CFG)" == "bsl - Win32 Release"


"$(INTDIR)\FNameStr.obj" : $(SOURCE) $(DEP_CPP_FNAME) "$(INTDIR)"\
 "$(INTDIR)\bsl.pch"


!ELSEIF  "$(CFG)" == "bsl - Win32 Debug"


"$(INTDIR)\FNameStr.obj" : $(SOURCE) $(DEP_CPP_FNAME) "$(INTDIR)"\
 "$(INTDIR)\bsl.pch"

"$(INTDIR)\FNameStr.sbr" : $(SOURCE) $(DEP_CPP_FNAME) "$(INTDIR)"\
 "$(INTDIR)\bsl.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\BslApp.cpp
DEP_CPP_BSLAP=\
	".\BclError.h"\
	".\bslapp.h"\
	".\bslp.h"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cstddef"\
	{$(INCLUDE)}"\cstdio"\
	{$(INCLUDE)}"\cstdlib"\
	{$(INCLUDE)}"\cstring"\
	{$(INCLUDE)}"\cwchar"\
	{$(INCLUDE)}"\exception"\
	{$(INCLUDE)}"\functional"\
	{$(INCLUDE)}"\ios"\
	{$(INCLUDE)}"\iosfwd"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\iterator"\
	{$(INCLUDE)}"\list"\
	{$(INCLUDE)}"\map"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
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
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
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
	{$(INCLUDE)}"\xtree"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	

!IF  "$(CFG)" == "bsl - Win32 Release"


"$(INTDIR)\BslApp.obj" : $(SOURCE) $(DEP_CPP_BSLAP) "$(INTDIR)"\
 "$(INTDIR)\bsl.pch"


!ELSEIF  "$(CFG)" == "bsl - Win32 Debug"


"$(INTDIR)\BslApp.obj" : $(SOURCE) $(DEP_CPP_BSLAP) "$(INTDIR)"\
 "$(INTDIR)\bsl.pch"

"$(INTDIR)\BslApp.sbr" : $(SOURCE) $(DEP_CPP_BSLAP) "$(INTDIR)"\
 "$(INTDIR)\bsl.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
