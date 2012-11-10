# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=MsgBlast - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to MsgBlast - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "MsgBlast - Win32 Release" && "$(CFG)" !=\
 "MsgBlast - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "MSGBLAST.MAK" CFG="MsgBlast - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MsgBlast - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MsgBlast - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "MsgBlast - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "MsgBlast - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WinRel"
# PROP Intermediate_Dir "WinRel"
OUTDIR=.\WinRel
INTDIR=.\WinRel
# Begin Custom Macros
TargetName=MsgBlast
# End Custom Macros

ALL : "$(OUTDIR)\MsgBlast.ext" "$(OUTDIR)\MSGBLAST.bsc"\
 "c:\trias.mvc\trias200.rel\MsgBlast.ext" "$(OUTDIR)\MsgBlast.tlb"

CLEAN : 
	-@erase "$(INTDIR)\Jumptab.obj"
	-@erase "$(INTDIR)\Jumptab.sbr"
	-@erase "$(INTDIR)\MsgBlast.obj"
	-@erase "$(INTDIR)\MSGBLAST.pch"
	-@erase "$(INTDIR)\MsgBlast.res"
	-@erase "$(INTDIR)\MsgBlast.sbr"
	-@erase "$(INTDIR)\MsgBlast.tlb"
	-@erase "$(INTDIR)\MsgBlastExt.obj"
	-@erase "$(INTDIR)\MsgBlastExt.sbr"
	-@erase "$(INTDIR)\MsgMap.obj"
	-@erase "$(INTDIR)\MsgMap.sbr"
	-@erase "$(INTDIR)\STDAFX.OBJ"
	-@erase "$(INTDIR)\STDAFX.SBR"
	-@erase "$(OUTDIR)\MSGBLAST.bsc"
	-@erase "$(OUTDIR)\MsgBlast.exp"
	-@erase "$(OUTDIR)\MsgBlast.ext"
	-@erase "$(OUTDIR)\MsgBlast.lib"
	-@erase ".\DMsgMap.h"
	-@erase ".\MsgBlast_i.c"
	-@erase "c:\trias.mvc\trias200.rel\MsgBlast.ext"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "QI_EXCEPTION" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D "OS_NO_STREAM_SUPPORT" /D "OS_NO_ALLOCATORS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "__MFC__" /D "EBWIN32" /FR /Yu"StdAfx.h" /c
CPP_PROJ=/nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D\
 "QI_EXCEPTION" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D\
 "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D "OS_NO_STREAM_SUPPORT"\
 /D "OS_NO_ALLOCATORS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D\
 "__MFC__" /D "EBWIN32" /FR"$(INTDIR)/" /Fp"$(INTDIR)/MSGBLAST.pch"\
 /Yu"StdAfx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\WinRel/
CPP_SBRS=.\WinRel/
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/MsgBlast.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/MSGBLAST.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Jumptab.sbr" \
	"$(INTDIR)\MsgBlast.sbr" \
	"$(INTDIR)\MsgBlastExt.sbr" \
	"$(INTDIR)\MsgMap.sbr" \
	"$(INTDIR)\STDAFX.SBR"

"$(OUTDIR)\MSGBLAST.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 Ixtmar42.lib stdcppr.lib TriasTlb.lib ospace2r.lib ebn.lib /nologo /subsystem:windows /dll /machine:I386 /stub:"rights.exe" /out:"WinRel/MsgBlast.ext"
LINK32_FLAGS=Ixtmar42.lib stdcppr.lib TriasTlb.lib ospace2r.lib ebn.lib /nologo\
 /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)/MsgBlast.pdb"\
 /machine:I386 /def:".\MsgBlast.DEF" /stub:"rights.exe"\
 /out:"$(OUTDIR)/MsgBlast.ext" /implib:"$(OUTDIR)/MsgBlast.lib" 
DEF_FILE= \
	".\MsgBlast.DEF"
LINK32_OBJS= \
	"$(INTDIR)\Jumptab.obj" \
	"$(INTDIR)\MsgBlast.obj" \
	"$(INTDIR)\MsgBlast.res" \
	"$(INTDIR)\MsgBlastExt.obj" \
	"$(INTDIR)\MsgMap.obj" \
	"$(INTDIR)\STDAFX.OBJ"

"$(OUTDIR)\MsgBlast.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying target to destination ...
TargetPath=.\WinRel\MsgBlast.ext
TargetName=MsgBlast
InputPath=.\WinRel\MsgBlast.ext
SOURCE=$(InputPath)

"c:\trias.mvc\trias200.rel\$(TargetName).ext" : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
   copy $(TargetPath) c:\trias.mvc\trias200.rel

# End Custom Build

!ELSEIF  "$(CFG)" == "MsgBlast - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinDebug"
# PROP Intermediate_Dir "WinDebug"
OUTDIR=.\WinDebug
INTDIR=.\WinDebug
# Begin Custom Macros
TargetName=MsgBlstd
# End Custom Macros

ALL : "$(OUTDIR)\MsgBlstd.ext" "$(OUTDIR)\MSGBLAST.bsc"\
 "c:\trias.mvc\trias200\MsgBlstd.ext"

CLEAN : 
	-@erase "$(INTDIR)\Jumptab.obj"
	-@erase "$(INTDIR)\Jumptab.sbr"
	-@erase "$(INTDIR)\MsgBlast.obj"
	-@erase "$(INTDIR)\MSGBLAST.pch"
	-@erase "$(INTDIR)\MsgBlast.res"
	-@erase "$(INTDIR)\MsgBlast.sbr"
	-@erase "$(INTDIR)\MsgBlast.tlb"
	-@erase "$(INTDIR)\MsgBlastExt.obj"
	-@erase "$(INTDIR)\MsgBlastExt.sbr"
	-@erase "$(INTDIR)\MsgMap.obj"
	-@erase "$(INTDIR)\MsgMap.sbr"
	-@erase "$(INTDIR)\STDAFX.OBJ"
	-@erase "$(INTDIR)\STDAFX.SBR"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\MSGBLAST.bsc"
	-@erase "$(OUTDIR)\MsgBlstd.exp"
	-@erase "$(OUTDIR)\MsgBlstd.ext"
	-@erase "$(OUTDIR)\MsgBlstd.ilk"
	-@erase "$(OUTDIR)\MsgBlstd.lib"
	-@erase "$(OUTDIR)\MsgBlstd.pdb"
	-@erase ".\DMsgMap.h"
	-@erase ".\MsgBlast_i.c"
	-@erase "c:\trias.mvc\trias200\MsgBlstd.ext"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "QI_EXCEPTION" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D "OS_NO_STREAM_SUPPORT" /D "OS_NO_ALLOCATORS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "__MFC__" /D "EBWIN32" /FR /Yu"StdAfx.h" /c
CPP_PROJ=/nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__"\
 /D "QI_EXCEPTION" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D\
 "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D "OS_NO_STREAM_SUPPORT"\
 /D "OS_NO_ALLOCATORS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D\
 "__MFC__" /D "EBWIN32" /FR"$(INTDIR)/" /Fp"$(INTDIR)/MSGBLAST.pch"\
 /Yu"StdAfx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\WinDebug/
CPP_SBRS=.\WinDebug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/MsgBlast.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/MSGBLAST.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Jumptab.sbr" \
	"$(INTDIR)\MsgBlast.sbr" \
	"$(INTDIR)\MsgBlastExt.sbr" \
	"$(INTDIR)\MsgMap.sbr" \
	"$(INTDIR)\STDAFX.SBR"

"$(OUTDIR)\MSGBLAST.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 Ixtmad42.lib stdcppd.lib TriasTld.lib ospace2d.lib ebn.lib /nologo /subsystem:windows /dll /debug /machine:I386 /stub:"rights.exe" /out:"WinDebug/MsgBlstd.ext"
LINK32_FLAGS=Ixtmad42.lib stdcppd.lib TriasTld.lib ospace2d.lib ebn.lib /nologo\
 /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)/MsgBlstd.pdb" /debug\
 /machine:I386 /def:".\MsgBlast.DEF" /stub:"rights.exe"\
 /out:"$(OUTDIR)/MsgBlstd.ext" /implib:"$(OUTDIR)/MsgBlstd.lib" 
DEF_FILE= \
	".\MsgBlast.DEF"
LINK32_OBJS= \
	"$(INTDIR)\Jumptab.obj" \
	"$(INTDIR)\MsgBlast.obj" \
	"$(INTDIR)\MsgBlast.res" \
	"$(INTDIR)\MsgBlastExt.obj" \
	"$(INTDIR)\MsgMap.obj" \
	"$(INTDIR)\STDAFX.OBJ"

"$(OUTDIR)\MsgBlstd.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying target to destination ...
TargetPath=.\WinDebug\MsgBlstd.ext
TargetName=MsgBlstd
InputPath=.\WinDebug\MsgBlstd.ext
SOURCE=$(InputPath)

"c:\trias.mvc\trias200\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   copy $(TargetPath) c:\trias.mvc\trias200

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

# Name "MsgBlast - Win32 Release"
# Name "MsgBlast - Win32 Debug"

!IF  "$(CFG)" == "MsgBlast - Win32 Release"

!ELSEIF  "$(CFG)" == "MsgBlast - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\MsgBlast.CXX
DEP_CPP_MSGBL=\
	".\DMsgMap.h"\
	".\MSGBLAST.HXX"\
	".\MSGGUID.H"\
	".\MsgMap.h"\
	".\STDAFX.H"\
	".\VERSION.H"\
	{$(INCLUDE)}"\bscrguid.h"\
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
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ocidl.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
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
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\MsgBlast.obj" : $(SOURCE) $(DEP_CPP_MSGBL) "$(INTDIR)"\
 "$(INTDIR)\MSGBLAST.pch" ".\DMsgMap.h"

"$(INTDIR)\MsgBlast.sbr" : $(SOURCE) $(DEP_CPP_MSGBL) "$(INTDIR)"\
 "$(INTDIR)\MSGBLAST.pch" ".\DMsgMap.h"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MsgBlast.RC
DEP_RSC_MSGBLA=\
	".\MsgBlast.RCV"\
	".\Res\MsgBlstp.rc"\
	".\Res\MsgMap.Rgs"\
	".\WinDebug\MsgBlast.tlb"\
	

"$(INTDIR)\MsgBlast.res" : $(SOURCE) $(DEP_RSC_MSGBLA) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MsgBlast.DEF

!IF  "$(CFG)" == "MsgBlast - Win32 Release"

!ELSEIF  "$(CFG)" == "MsgBlast - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STDAFX.CPP
DEP_CPP_STDAF=\
	".\DMsgMap.h"\
	".\MSGBLAST.HXX"\
	".\MsgBlast_i.c"\
	".\MSGGUID.H"\
	".\STDAFX.H"\
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
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ocidl.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
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
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "MsgBlast - Win32 Release"

# ADD CPP /Yc"StdAfx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D\
 "QI_EXCEPTION" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D\
 "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D "OS_NO_STREAM_SUPPORT"\
 /D "OS_NO_ALLOCATORS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D\
 "__MFC__" /D "EBWIN32" /FR"$(INTDIR)/" /Fp"$(INTDIR)/MSGBLAST.pch"\
 /Yc"StdAfx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\STDAFX.OBJ" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"\
 ".\MsgBlast_i.c" ".\DMsgMap.h"
   $(BuildCmds)

"$(INTDIR)\STDAFX.SBR" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"\
 ".\MsgBlast_i.c" ".\DMsgMap.h"
   $(BuildCmds)

"$(INTDIR)\MSGBLAST.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"\
 ".\MsgBlast_i.c" ".\DMsgMap.h"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "MsgBlast - Win32 Debug"

# ADD CPP /Yc"StdAfx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__"\
 /D "QI_EXCEPTION" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D\
 "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D "OS_NO_STREAM_SUPPORT"\
 /D "OS_NO_ALLOCATORS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D\
 "__MFC__" /D "EBWIN32" /FR"$(INTDIR)/" /Fp"$(INTDIR)/MSGBLAST.pch"\
 /Yc"StdAfx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\STDAFX.OBJ" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"\
 ".\MsgBlast_i.c" ".\DMsgMap.h"
   $(BuildCmds)

"$(INTDIR)\STDAFX.SBR" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"\
 ".\MsgBlast_i.c" ".\DMsgMap.h"
   $(BuildCmds)

"$(INTDIR)\MSGBLAST.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"\
 ".\MsgBlast_i.c" ".\DMsgMap.h"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MsgBlastExt.cpp
DEP_CPP_MSGBLAS=\
	".\DMsgMap.h"\
	".\Jumptab.h"\
	".\MSGBLAST.HXX"\
	".\MSGGUID.H"\
	".\STDAFX.H"\
	{$(INCLUDE)}"\bscrerr.h"\
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
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ocidl.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
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
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Trace.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\MsgBlastExt.obj" : $(SOURCE) $(DEP_CPP_MSGBLAS) "$(INTDIR)"\
 "$(INTDIR)\MSGBLAST.pch" ".\DMsgMap.h"

"$(INTDIR)\MsgBlastExt.sbr" : $(SOURCE) $(DEP_CPP_MSGBLAS) "$(INTDIR)"\
 "$(INTDIR)\MSGBLAST.pch" ".\DMsgMap.h"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Jumptab.cpp
DEP_CPP_JUMPT=\
	".\DMsgMap.h"\
	".\Jumptab.h"\
	".\MSGBLAST.HXX"\
	".\MsgBlastExt.h"\
	".\MSGGUID.H"\
	".\STDAFX.H"\
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
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ocidl.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
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
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\Jumptab.obj" : $(SOURCE) $(DEP_CPP_JUMPT) "$(INTDIR)"\
 "$(INTDIR)\MSGBLAST.pch" ".\DMsgMap.h"

"$(INTDIR)\Jumptab.sbr" : $(SOURCE) $(DEP_CPP_JUMPT) "$(INTDIR)"\
 "$(INTDIR)\MSGBLAST.pch" ".\DMsgMap.h"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MsgBlast.idl

!IF  "$(CFG)" == "MsgBlast - Win32 Release"

# Begin Custom Build - Running MIDL ...
OutDir=.\WinRel
InputPath=.\MsgBlast.idl
InputName=MsgBlast

BuildCmds= \
	midl /old /win32 /h "DMsgMap.h" /iid "$(InputName)_i.c" $(InputPath) \
	

"$(OutDir)\$(InputName).tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

""$(InputName)_i.c"" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

""DMsgMap.h"" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "MsgBlast - Win32 Debug"

# Begin Custom Build - Running MIDL ...
OutDir=.\WinDebug
InputPath=.\MsgBlast.idl
InputName=MsgBlast

BuildCmds= \
	midl /old /win32 /h "DMsgMap.h" /iid "$(InputName)_i.c" $(InputPath) \
	

"$(OutDir)\$(InputName).tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

""$(InputName)_i.c"" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

""DMsgMap.h"" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MsgMap.cpp

!IF  "$(CFG)" == "MsgBlast - Win32 Release"

DEP_CPP_MSGMA=\
	".\DMsgMap.h"\
	".\MsgMap.h"\
	".\STDAFX.H"\
	{$(INCLUDE)}"\bscrguid.h"\
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
	{$(INCLUDE)}"\dirisole.h"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ocidl.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
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
	

"$(INTDIR)\MsgMap.obj" : $(SOURCE) $(DEP_CPP_MSGMA) "$(INTDIR)"\
 "$(INTDIR)\MSGBLAST.pch" ".\DMsgMap.h"

"$(INTDIR)\MsgMap.sbr" : $(SOURCE) $(DEP_CPP_MSGMA) "$(INTDIR)"\
 "$(INTDIR)\MSGBLAST.pch" ".\DMsgMap.h"


!ELSEIF  "$(CFG)" == "MsgBlast - Win32 Debug"

DEP_CPP_MSGMA=\
	".\DMsgMap.h"\
	".\MsgMap.h"\
	".\STDAFX.H"\
	{$(INCLUDE)}"\bscrguid.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\dirisole.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ocidl.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\MsgMap.obj" : $(SOURCE) $(DEP_CPP_MSGMA) "$(INTDIR)"\
 "$(INTDIR)\MSGBLAST.pch" ".\DMsgMap.h"

"$(INTDIR)\MsgMap.sbr" : $(SOURCE) $(DEP_CPP_MSGMA) "$(INTDIR)"\
 "$(INTDIR)\MSGBLAST.pch" ".\DMsgMap.h"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
