# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Helper - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Helper - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Helper - Win32 Release" && "$(CFG)" != "Helper - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "HELPER.MAK" CFG="Helper - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Helper - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Helper - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "Helper - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "Helper - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release.207"
# PROP Intermediate_Dir "Release.207"
# PROP Target_Dir ""
OUTDIR=.\Release.207
INTDIR=.\Release.207

ALL : "$(OUTDIR)\HELPER.dll" "c:\trias.mvc\trias200.rel\Helper.dll"

CLEAN : 
	-@erase "$(INTDIR)\Helper.obj"
	-@erase "$(INTDIR)\HELPER.pch"
	-@erase "$(INTDIR)\Helper.res"
	-@erase "$(INTDIR)\RegExpr.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StringPair.obj"
	-@erase "$(OUTDIR)\HELPER.dll"
	-@erase "$(OUTDIR)\HELPER.exp"
	-@erase "$(OUTDIR)\HELPER.lib"
	-@erase ".\Helper.h"
	-@erase ".\Helper.tlb"
	-@erase ".\Helper_i.c"
	-@erase "c:\trias.mvc\trias200.rel\Helper.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "__ATL_USED__" /D "QI_EXCEPTION" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "NOMINMAX" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D "OS_NO_STREAM_SUPPORT" /D "OS_NO_ALLOCATORS" /D "__ATL_11_USED__" /D "ATL_NO_NAMESSPACE" /D "_ATL_NEW_CCOMSTRUCT" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GR /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "__ATL_USED__" /D\
 "QI_EXCEPTION" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D\
 "NOMINMAX" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D\
 "OS_NO_STREAM_SUPPORT" /D "OS_NO_ALLOCATORS" /D "__ATL_11_USED__" /D\
 "ATL_NO_NAMESSPACE" /D "_ATL_NEW_CCOMSTRUCT" /Fp"$(INTDIR)/HELPER.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release.207/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/Helper.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/HELPER.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ospace2r.lib /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=ospace2r.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/HELPER.pdb" /machine:I386 /def:".\Helper.def"\
 /out:"$(OUTDIR)/HELPER.dll" /implib:"$(OUTDIR)/HELPER.lib" 
DEF_FILE= \
	".\Helper.def"
LINK32_OBJS= \
	"$(INTDIR)\Helper.obj" \
	"$(INTDIR)\Helper.res" \
	"$(INTDIR)\RegExpr.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\StringPair.obj"

"$(OUTDIR)\HELPER.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying target to destination ...
TargetPath=.\Release.207\HELPER.dll
InputPath=.\Release.207\HELPER.dll
SOURCE=$(InputPath)

"c:\trias.mvc\trias200.rel\Helper.dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   copy $(TargetPath) c:\trias.mvc\trias200.rel

# End Custom Build

!ELSEIF  "$(CFG)" == "Helper - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug.207"
# PROP Intermediate_Dir "Debug.207"
# PROP Target_Dir ""
OUTDIR=.\Debug.207
INTDIR=.\Debug.207

ALL : "$(OUTDIR)\Helperd.dll" "$(OUTDIR)\HELPER.bsc"

CLEAN : 
	-@erase "$(INTDIR)\Helper.obj"
	-@erase "$(INTDIR)\HELPER.pch"
	-@erase "$(INTDIR)\Helper.res"
	-@erase "$(INTDIR)\Helper.sbr"
	-@erase "$(INTDIR)\RegExpr.obj"
	-@erase "$(INTDIR)\RegExpr.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\StringPair.obj"
	-@erase "$(INTDIR)\StringPair.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\HELPER.bsc"
	-@erase "$(OUTDIR)\Helperd.dll"
	-@erase "$(OUTDIR)\Helperd.exp"
	-@erase "$(OUTDIR)\Helperd.ilk"
	-@erase "$(OUTDIR)\Helperd.lib"
	-@erase "$(OUTDIR)\Helperd.pdb"
	-@erase ".\Helper.h"
	-@erase ".\Helper.tlb"
	-@erase ".\Helper_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "__ATL_USED__" /D "QI_EXCEPTION" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "NOMINMAX" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D "OS_NO_STREAM_SUPPORT" /D "OS_NO_ALLOCATORS" /D "__ATL_11_USED__" /D "ATL_NO_NAMESSPACE" /D "_ATL_NEW_CCOMSTRUCT" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GR /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "__ATL_USED__"\
 /D "QI_EXCEPTION" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D\
 "NOMINMAX" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D\
 "OS_NO_STREAM_SUPPORT" /D "OS_NO_ALLOCATORS" /D "__ATL_11_USED__" /D\
 "ATL_NO_NAMESSPACE" /D "_ATL_NEW_CCOMSTRUCT" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/HELPER.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug.207/
CPP_SBRS=.\Debug.207/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/Helper.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/HELPER.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Helper.sbr" \
	"$(INTDIR)\RegExpr.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\StringPair.sbr"

"$(OUTDIR)\HELPER.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 ospace2d.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"Debug.207/Helperd.dll"
LINK32_FLAGS=ospace2d.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/Helperd.pdb" /debug /machine:I386 /def:".\Helper.def"\
 /out:"$(OUTDIR)/Helperd.dll" /implib:"$(OUTDIR)/Helperd.lib" 
DEF_FILE= \
	".\Helper.def"
LINK32_OBJS= \
	"$(INTDIR)\Helper.obj" \
	"$(INTDIR)\Helper.res" \
	"$(INTDIR)\RegExpr.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\StringPair.obj"

"$(OUTDIR)\Helperd.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Helper - Win32 Release"
# Name "Helper - Win32 Debug"

!IF  "$(CFG)" == "Helper - Win32 Release"

!ELSEIF  "$(CFG)" == "Helper - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\StringPair.cpp

!IF  "$(CFG)" == "Helper - Win32 Release"

DEP_CPP_STRIN=\
	".\Helper.h"\
	".\StdAfx.h"\
	".\StringPair.h"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
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
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
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
	{$(INCLUDE)}"\ospace\string\tokenize.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\StringPair.obj" : $(SOURCE) $(DEP_CPP_STRIN) "$(INTDIR)"\
 "$(INTDIR)\HELPER.pch" ".\Helper.h"


!ELSEIF  "$(CFG)" == "Helper - Win32 Debug"

DEP_CPP_STRIN=\
	".\Helper.h"\
	".\StdAfx.h"\
	".\StringPair.h"\
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
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ospace\com\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"\ospace\com\smartif.h"\
	{$(INCLUDE)}"\ospace\com\smartif.nodebug.h"\
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
	{$(INCLUDE)}"\ospace\std\vector"\
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
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\tokenize.h"\
	{$(INCLUDE)}"\ospace\string\tokenize.ipp"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\vector"\
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
	

"$(INTDIR)\StringPair.obj" : $(SOURCE) $(DEP_CPP_STRIN) "$(INTDIR)"\
 "$(INTDIR)\HELPER.pch" ".\Helper.h"

"$(INTDIR)\StringPair.sbr" : $(SOURCE) $(DEP_CPP_STRIN) "$(INTDIR)"\
 "$(INTDIR)\HELPER.pch" ".\Helper.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Helper.rc
DEP_RSC_HELPE=\
	".\Helper.tlb"\
	".\RegExpr.rgs"\
	".\StringPair.rgs"\
	

"$(INTDIR)\Helper.res" : $(SOURCE) $(DEP_RSC_HELPE) "$(INTDIR)" ".\Helper.tlb"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\RegExpr.cpp

!IF  "$(CFG)" == "Helper - Win32 Release"

DEP_CPP_REGEX=\
	".\Helper.h"\
	".\PersistHelper.h"\
	".\RegExpr.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\atlcomx.h"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\iostream"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\helper.h"\
	{$(INCLUDE)}"\ospace\except\helper.ipp"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\stdexcept"\
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
	{$(INCLUDE)}"\ospace\string\regexp.h"\
	{$(INCLUDE)}"\ospace\string\regexp.ipp"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\src\regex.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\substr.cc"\
	{$(INCLUDE)}"\ospace\string\substr.h"\
	{$(INCLUDE)}"\ospace\string\substr.ipp"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\RegExpr.obj" : $(SOURCE) $(DEP_CPP_REGEX) "$(INTDIR)"\
 "$(INTDIR)\HELPER.pch" ".\Helper.h"


!ELSEIF  "$(CFG)" == "Helper - Win32 Debug"

DEP_CPP_REGEX=\
	".\Helper.h"\
	".\PersistHelper.h"\
	".\RegExpr.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\atlcomx.h"\
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
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\iostream"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ospace\com\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"\ospace\com\smartif.h"\
	{$(INCLUDE)}"\ospace\com\smartif.nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\helper.h"\
	{$(INCLUDE)}"\ospace\except\helper.ipp"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\stdexcept"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\regexp.h"\
	{$(INCLUDE)}"\ospace\string\regexp.ipp"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\src\regex.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\substr.cc"\
	{$(INCLUDE)}"\ospace\string\substr.h"\
	{$(INCLUDE)}"\ospace\string\substr.ipp"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
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
	

"$(INTDIR)\RegExpr.obj" : $(SOURCE) $(DEP_CPP_REGEX) "$(INTDIR)"\
 "$(INTDIR)\HELPER.pch" ".\Helper.h"

"$(INTDIR)\RegExpr.sbr" : $(SOURCE) $(DEP_CPP_REGEX) "$(INTDIR)"\
 "$(INTDIR)\HELPER.pch" ".\Helper.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\atlimpl.cpp"\
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
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\com\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"\ospace\com\smartif.h"\
	{$(INCLUDE)}"\ospace\com\smartif.nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
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
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
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
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
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
	

!IF  "$(CFG)" == "Helper - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GR /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "__ATL_USED__" /D\
 "QI_EXCEPTION" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D\
 "NOMINMAX" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D\
 "OS_NO_STREAM_SUPPORT" /D "OS_NO_ALLOCATORS" /D "__ATL_11_USED__" /D\
 "ATL_NO_NAMESSPACE" /D "_ATL_NEW_CCOMSTRUCT" /Fp"$(INTDIR)/HELPER.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\HELPER.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Helper - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GR /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "__ATL_USED__"\
 /D "QI_EXCEPTION" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D\
 "NOMINMAX" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D\
 "OS_NO_STREAM_SUPPORT" /D "OS_NO_ALLOCATORS" /D "__ATL_11_USED__" /D\
 "ATL_NO_NAMESSPACE" /D "_ATL_NEW_CCOMSTRUCT" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/HELPER.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\HELPER.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Helper.cpp

!IF  "$(CFG)" == "Helper - Win32 Release"

DEP_CPP_HELPER=\
	".\Helper.h"\
	".\Helper_i.c"\
	".\RegExpr.h"\
	".\StdAfx.h"\
	".\StringPair.h"\
	{$(INCLUDE)}"\atlcomx.h"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\iostream"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\helper.h"\
	{$(INCLUDE)}"\ospace\except\helper.ipp"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\stdexcept"\
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
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
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
	{$(INCLUDE)}"\ospace\string\regexp.h"\
	{$(INCLUDE)}"\ospace\string\regexp.ipp"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\src\regex.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\substr.cc"\
	{$(INCLUDE)}"\ospace\string\substr.h"\
	{$(INCLUDE)}"\ospace\string\substr.ipp"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\Helper.obj" : $(SOURCE) $(DEP_CPP_HELPER) "$(INTDIR)"\
 "$(INTDIR)\HELPER.pch" ".\Helper.h" ".\Helper_i.c"


!ELSEIF  "$(CFG)" == "Helper - Win32 Debug"

DEP_CPP_HELPER=\
	".\Helper.h"\
	".\Helper_i.c"\
	".\RegExpr.h"\
	".\StdAfx.h"\
	".\StringPair.h"\
	{$(INCLUDE)}"\atlcomx.h"\
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
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\iostream"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ospace\com\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"\ospace\com\smartif.h"\
	{$(INCLUDE)}"\ospace\com\smartif.nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\helper.h"\
	{$(INCLUDE)}"\ospace\except\helper.ipp"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\stdexcept"\
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
	{$(INCLUDE)}"\ospace\string\regexp.h"\
	{$(INCLUDE)}"\ospace\string\regexp.ipp"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\src\regex.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\substr.cc"\
	{$(INCLUDE)}"\ospace\string\substr.h"\
	{$(INCLUDE)}"\ospace\string\substr.ipp"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
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
	

"$(INTDIR)\Helper.obj" : $(SOURCE) $(DEP_CPP_HELPER) "$(INTDIR)"\
 "$(INTDIR)\HELPER.pch" ".\Helper.h" ".\Helper_i.c"

"$(INTDIR)\Helper.sbr" : $(SOURCE) $(DEP_CPP_HELPER) "$(INTDIR)"\
 "$(INTDIR)\HELPER.pch" ".\Helper.h" ".\Helper_i.c"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RegExpr.rgs

!IF  "$(CFG)" == "Helper - Win32 Release"

!ELSEIF  "$(CFG)" == "Helper - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StringPair.rgs

!IF  "$(CFG)" == "Helper - Win32 Release"

!ELSEIF  "$(CFG)" == "Helper - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Helper.idl

!IF  "$(CFG)" == "Helper - Win32 Release"

# Begin Custom Build
InputPath=.\Helper.idl

BuildCmds= \
	midl /Oicf /old /h "Helper.h" /iid "Helper_i.c" "Helper.idl" \
	

".\Helper.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Helper_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Helper.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Helper - Win32 Debug"

# Begin Custom Build
InputPath=.\Helper.idl

BuildCmds= \
	midl /Oicf /old /h "Helper.h" /iid "Helper_i.c" "Helper.idl" \
	

".\Helper.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Helper_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Helper.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Helper.def

!IF  "$(CFG)" == "Helper - Win32 Release"

!ELSEIF  "$(CFG)" == "Helper - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
