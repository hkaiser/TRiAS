# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Feature - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Feature - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Feature - Win32 Release" && "$(CFG)" !=\
 "Feature - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Feature.mak" CFG="Feature - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Feature - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Feature - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "Feature - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "Feature - Win32 Release"

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
# Begin Custom Macros
TargetName=Feature
# End Custom Macros

ALL : "$(OUTDIR)\Feature.ext" "c:\trias.mvc\trias200.rel\Feature.ext"

CLEAN : 
	-@erase "$(INTDIR)\Cgobject.obj"
	-@erase "$(INTDIR)\Classdlg.obj"
	-@erase "$(INTDIR)\Featmenu.obj"
	-@erase "$(INTDIR)\Feature.pch"
	-@erase "$(INTDIR)\Feature.res"
	-@erase "$(INTDIR)\Featurep.obj"
	-@erase "$(INTDIR)\Featurex.obj"
	-@erase "$(INTDIR)\Selident.obj"
	-@erase "$(INTDIR)\Selidlst.obj"
	-@erase "$(INTDIR)\UIDOBJ.OBJ"
	-@erase "$(OUTDIR)\Feature.exp"
	-@erase "$(OUTDIR)\Feature.ext"
	-@erase "$(OUTDIR)\Feature.lib"
	-@erase "c:\trias.mvc\trias200.rel\Feature.ext"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /G3 /MT /W3 /WX /Ox /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "__CV__" /D "STRICT" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /Ox /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "__CV__" /D "STRICT" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /Yu"featurep.hxx" /c
CPP_PROJ=/nologo /MD /W3 /WX /GX /Ox /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "__CV__" /D "STRICT" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__"\
 /Fp"$(INTDIR)/Feature.pch" /Yu"featurep.hxx" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/Feature.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Feature.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 ixtnsn16.lib framelib.lib typelib.lib lstrdw.lib oldnames.lib ldllcew.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:IX86
# ADD LINK32 ixtnsr40.lib tfrmwork.lib cont32r.lib stdcppr.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:IX86 /out:"Release/Feature.ext"
LINK32_FLAGS=ixtnsr40.lib tfrmwork.lib cont32r.lib stdcppr.lib winmm.lib\
 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib\
 shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo\
 /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)/Feature.pdb"\
 /machine:IX86 /def:".\Merkmal.def" /out:"$(OUTDIR)/Feature.ext"\
 /implib:"$(OUTDIR)/Feature.lib" 
DEF_FILE= \
	".\Merkmal.def"
LINK32_OBJS= \
	"$(INTDIR)\Cgobject.obj" \
	"$(INTDIR)\Classdlg.obj" \
	"$(INTDIR)\Featmenu.obj" \
	"$(INTDIR)\Feature.res" \
	"$(INTDIR)\Featurep.obj" \
	"$(INTDIR)\Featurex.obj" \
	"$(INTDIR)\Selident.obj" \
	"$(INTDIR)\Selidlst.obj" \
	"$(INTDIR)\UIDOBJ.OBJ"

"$(OUTDIR)\Feature.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
TargetPath=.\Release\Feature.ext
TargetName=Feature
InputPath=.\Release\Feature.ext
SOURCE=$(InputPath)

"c:\trias.mvc\trias200.rel\$(TargetName).ext" : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
   copy $(TargetPath) c:\trias.mvc\trias200.rel

# End Custom Build

!ELSEIF  "$(CFG)" == "Feature - Win32 Debug"

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
TargetName=merkmal
# End Custom Macros

ALL : "$(OUTDIR)\merkmal.ext" "$(OUTDIR)\Feature.bsc"\
 "c:\trias.mvc\trias200\merkmal.ext"

CLEAN : 
	-@erase "$(INTDIR)\Cgobject.obj"
	-@erase "$(INTDIR)\Cgobject.sbr"
	-@erase "$(INTDIR)\Classdlg.obj"
	-@erase "$(INTDIR)\Classdlg.sbr"
	-@erase "$(INTDIR)\Featmenu.obj"
	-@erase "$(INTDIR)\Featmenu.sbr"
	-@erase "$(INTDIR)\Feature.pch"
	-@erase "$(INTDIR)\Feature.res"
	-@erase "$(INTDIR)\Featurep.obj"
	-@erase "$(INTDIR)\Featurep.sbr"
	-@erase "$(INTDIR)\Featurex.obj"
	-@erase "$(INTDIR)\Featurex.sbr"
	-@erase "$(INTDIR)\Selident.obj"
	-@erase "$(INTDIR)\Selident.sbr"
	-@erase "$(INTDIR)\Selidlst.obj"
	-@erase "$(INTDIR)\Selidlst.sbr"
	-@erase "$(INTDIR)\UIDOBJ.OBJ"
	-@erase "$(INTDIR)\UIDOBJ.SBR"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Feature.bsc"
	-@erase "$(OUTDIR)\merkmal.exp"
	-@erase "$(OUTDIR)\merkmal.ext"
	-@erase "$(OUTDIR)\merkmal.ilk"
	-@erase "$(OUTDIR)\merkmal.lib"
	-@erase "$(OUTDIR)\merkmal.pdb"
	-@erase "c:\trias.mvc\trias200\merkmal.ext"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /WX /Gm /Zi /Od /Ob1 /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "__CV__" /D "STRICT" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "__CV__" /D "STRICT" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /FR /Yu"featurep.hxx" /c
CPP_PROJ=/nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "__CV__" /D "STRICT" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D\
 "__XTNSNDLL__" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Feature.pch" /Yu"featurep.hxx"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/Feature.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Feature.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Cgobject.sbr" \
	"$(INTDIR)\Classdlg.sbr" \
	"$(INTDIR)\Featmenu.sbr" \
	"$(INTDIR)\Featurep.sbr" \
	"$(INTDIR)\Featurex.sbr" \
	"$(INTDIR)\Selident.sbr" \
	"$(INTDIR)\Selidlst.sbr" \
	"$(INTDIR)\UIDOBJ.SBR"

"$(OUTDIR)\Feature.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 ixtnsn16.lib framelib.lib containr.lib lstrdwd.lib typelib.lib oldnames.lib ldllcew.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /map:"FULL" /debug /machine:IX86
# ADD LINK32 ixtnsd40.lib tfrm32d.lib cont32d.lib stdcppd.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:IX86 /out:"Debug/merkmal.ext"
# SUBTRACT LINK32 /map
LINK32_FLAGS=ixtnsd40.lib tfrm32d.lib cont32d.lib stdcppd.lib winmm.lib\
 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib\
 shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo\
 /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)/merkmal.pdb" /debug\
 /machine:IX86 /def:".\Merkmal.def" /out:"$(OUTDIR)/merkmal.ext"\
 /implib:"$(OUTDIR)/merkmal.lib" 
DEF_FILE= \
	".\Merkmal.def"
LINK32_OBJS= \
	"$(INTDIR)\Cgobject.obj" \
	"$(INTDIR)\Classdlg.obj" \
	"$(INTDIR)\Featmenu.obj" \
	"$(INTDIR)\Feature.res" \
	"$(INTDIR)\Featurep.obj" \
	"$(INTDIR)\Featurex.obj" \
	"$(INTDIR)\Selident.obj" \
	"$(INTDIR)\Selidlst.obj" \
	"$(INTDIR)\UIDOBJ.OBJ"

"$(OUTDIR)\merkmal.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
TargetPath=.\Debug\merkmal.ext
TargetName=merkmal
InputPath=.\Debug\merkmal.ext
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

# Name "Feature - Win32 Release"
# Name "Feature - Win32 Debug"

!IF  "$(CFG)" == "Feature - Win32 Release"

!ELSEIF  "$(CFG)" == "Feature - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Featurep.cxx
DEP_CPP_FEATU=\
	".\FEATURE.HXX"\
	".\Featurep.hxx"\
	".\UIDOBJ.HXX"\
	".\UIDOBJ.INL"\
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
	{$(INCLUDE)}"\Eieruhr.hxx"\
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
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
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
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\stdexcept"\
	{$(INCLUDE)}"\STRDUPX.HXX"\
	{$(INCLUDE)}"\streambuf"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\typeinfo"\
	{$(INCLUDE)}"\use_ansi.h"\
	{$(INCLUDE)}"\utility"\
	{$(INCLUDE)}"\VERSIONS.H"\
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
	

!IF  "$(CFG)" == "Feature - Win32 Release"

# ADD CPP /Yc"featurep.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /Ox /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "__CV__" /D "STRICT" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__"\
 /Fp"$(INTDIR)/Feature.pch" /Yc"featurep.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\Featurep.obj" : $(SOURCE) $(DEP_CPP_FEATU) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Feature.pch" : $(SOURCE) $(DEP_CPP_FEATU) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Feature - Win32 Debug"

# ADD CPP /Yc"featurep.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "__CV__" /D "STRICT" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D\
 "__XTNSNDLL__" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Feature.pch" /Yc"featurep.hxx"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\Featurep.obj" : $(SOURCE) $(DEP_CPP_FEATU) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Featurep.sbr" : $(SOURCE) $(DEP_CPP_FEATU) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Feature.pch" : $(SOURCE) $(DEP_CPP_FEATU) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Feature.rc

!IF  "$(CFG)" == "Feature - Win32 Release"


"$(INTDIR)\Feature.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Feature - Win32 Debug"

NODEP_RSC_FEATUR=\
	".\feature.rcv"\
	

"$(INTDIR)\Feature.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Featmenu.cxx
DEP_CPP_FEATM=\
	".\CGOBJECT.HXX"\
	".\CLASSDLG.HXX"\
	".\FEATURE.HXX"\
	".\Featurep.hxx"\
	".\SELIDENT.HXX"\
	".\SELIDLST.HXX"\
	".\UIDOBJ.HXX"\
	".\UIDOBJ.INL"\
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
	{$(INCLUDE)}"\Eieruhr.hxx"\
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
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
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
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\stdexcept"\
	{$(INCLUDE)}"\STRDUPX.HXX"\
	{$(INCLUDE)}"\streambuf"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\typeinfo"\
	{$(INCLUDE)}"\use_ansi.h"\
	{$(INCLUDE)}"\utility"\
	{$(INCLUDE)}"\VERSIONS.H"\
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
	

!IF  "$(CFG)" == "Feature - Win32 Release"


"$(INTDIR)\Featmenu.obj" : $(SOURCE) $(DEP_CPP_FEATM) "$(INTDIR)"\
 "$(INTDIR)\Feature.pch"


!ELSEIF  "$(CFG)" == "Feature - Win32 Debug"


"$(INTDIR)\Featmenu.obj" : $(SOURCE) $(DEP_CPP_FEATM) "$(INTDIR)"\
 "$(INTDIR)\Feature.pch"

"$(INTDIR)\Featmenu.sbr" : $(SOURCE) $(DEP_CPP_FEATM) "$(INTDIR)"\
 "$(INTDIR)\Feature.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Selidlst.cxx
DEP_CPP_SELID=\
	".\FEATURE.HXX"\
	".\Featurep.hxx"\
	".\SELIDLST.HXX"\
	".\UIDOBJ.HXX"\
	".\UIDOBJ.INL"\
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
	{$(INCLUDE)}"\Eieruhr.hxx"\
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
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
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
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\stdexcept"\
	{$(INCLUDE)}"\STRDUPX.HXX"\
	{$(INCLUDE)}"\streambuf"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\typeinfo"\
	{$(INCLUDE)}"\use_ansi.h"\
	{$(INCLUDE)}"\utility"\
	{$(INCLUDE)}"\VERSIONS.H"\
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
	

!IF  "$(CFG)" == "Feature - Win32 Release"


"$(INTDIR)\Selidlst.obj" : $(SOURCE) $(DEP_CPP_SELID) "$(INTDIR)"\
 "$(INTDIR)\Feature.pch"


!ELSEIF  "$(CFG)" == "Feature - Win32 Debug"


"$(INTDIR)\Selidlst.obj" : $(SOURCE) $(DEP_CPP_SELID) "$(INTDIR)"\
 "$(INTDIR)\Feature.pch"

"$(INTDIR)\Selidlst.sbr" : $(SOURCE) $(DEP_CPP_SELID) "$(INTDIR)"\
 "$(INTDIR)\Feature.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Selident.cxx
DEP_CPP_SELIDE=\
	".\FEATURE.HXX"\
	".\Featurep.hxx"\
	".\SELIDENT.HXX"\
	".\SELIDLST.HXX"\
	".\UIDOBJ.HXX"\
	".\UIDOBJ.INL"\
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
	{$(INCLUDE)}"\Eieruhr.hxx"\
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
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
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
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\stdexcept"\
	{$(INCLUDE)}"\STRDUPX.HXX"\
	{$(INCLUDE)}"\streambuf"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\typeinfo"\
	{$(INCLUDE)}"\use_ansi.h"\
	{$(INCLUDE)}"\utility"\
	{$(INCLUDE)}"\VERSIONS.H"\
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
	

!IF  "$(CFG)" == "Feature - Win32 Release"


"$(INTDIR)\Selident.obj" : $(SOURCE) $(DEP_CPP_SELIDE) "$(INTDIR)"\
 "$(INTDIR)\Feature.pch"


!ELSEIF  "$(CFG)" == "Feature - Win32 Debug"


"$(INTDIR)\Selident.obj" : $(SOURCE) $(DEP_CPP_SELIDE) "$(INTDIR)"\
 "$(INTDIR)\Feature.pch"

"$(INTDIR)\Selident.sbr" : $(SOURCE) $(DEP_CPP_SELIDE) "$(INTDIR)"\
 "$(INTDIR)\Feature.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\UIDOBJ.CXX
DEP_CPP_UIDOB=\
	".\FEATURE.HXX"\
	".\Featurep.hxx"\
	".\UIDOBJ.HXX"\
	".\UIDOBJ.INL"\
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
	{$(INCLUDE)}"\Eieruhr.hxx"\
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
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
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
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\stdexcept"\
	{$(INCLUDE)}"\STRDUPX.HXX"\
	{$(INCLUDE)}"\streambuf"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\typeinfo"\
	{$(INCLUDE)}"\use_ansi.h"\
	{$(INCLUDE)}"\utility"\
	{$(INCLUDE)}"\VERSIONS.H"\
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
	

!IF  "$(CFG)" == "Feature - Win32 Release"


"$(INTDIR)\UIDOBJ.OBJ" : $(SOURCE) $(DEP_CPP_UIDOB) "$(INTDIR)"\
 "$(INTDIR)\Feature.pch"


!ELSEIF  "$(CFG)" == "Feature - Win32 Debug"


"$(INTDIR)\UIDOBJ.OBJ" : $(SOURCE) $(DEP_CPP_UIDOB) "$(INTDIR)"\
 "$(INTDIR)\Feature.pch"

"$(INTDIR)\UIDOBJ.SBR" : $(SOURCE) $(DEP_CPP_UIDOB) "$(INTDIR)"\
 "$(INTDIR)\Feature.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Featurex.cxx
DEP_CPP_FEATURE=\
	".\CGOBJECT.HXX"\
	".\FEATGUID.H"\
	".\FEATURE.HXX"\
	".\Featurep.hxx"\
	".\UIDOBJ.HXX"\
	".\UIDOBJ.INL"\
	".\VERSIO32.H"\
	".\VERSION.H"\
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
	{$(INCLUDE)}"\Eieruhr.hxx"\
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
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
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
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\stdexcept"\
	{$(INCLUDE)}"\STRDUPX.HXX"\
	{$(INCLUDE)}"\streambuf"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\typeinfo"\
	{$(INCLUDE)}"\use_ansi.h"\
	{$(INCLUDE)}"\utility"\
	{$(INCLUDE)}"\VERSIONS.H"\
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
	
NODEP_CPP_FEATURE=\
	".\versio16.h"\
	

!IF  "$(CFG)" == "Feature - Win32 Release"


"$(INTDIR)\Featurex.obj" : $(SOURCE) $(DEP_CPP_FEATURE) "$(INTDIR)"\
 "$(INTDIR)\Feature.pch"


!ELSEIF  "$(CFG)" == "Feature - Win32 Debug"


"$(INTDIR)\Featurex.obj" : $(SOURCE) $(DEP_CPP_FEATURE) "$(INTDIR)"\
 "$(INTDIR)\Feature.pch"

"$(INTDIR)\Featurex.sbr" : $(SOURCE) $(DEP_CPP_FEATURE) "$(INTDIR)"\
 "$(INTDIR)\Feature.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Classdlg.cxx
DEP_CPP_CLASS=\
	".\CLASSDLG.HXX"\
	".\FEATURE.HXX"\
	".\Featurep.hxx"\
	".\UIDOBJ.HXX"\
	".\UIDOBJ.INL"\
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
	{$(INCLUDE)}"\Eieruhr.hxx"\
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
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
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
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\stdexcept"\
	{$(INCLUDE)}"\STRDUPX.HXX"\
	{$(INCLUDE)}"\streambuf"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\typeinfo"\
	{$(INCLUDE)}"\use_ansi.h"\
	{$(INCLUDE)}"\utility"\
	{$(INCLUDE)}"\VERSIONS.H"\
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
	

!IF  "$(CFG)" == "Feature - Win32 Release"


"$(INTDIR)\Classdlg.obj" : $(SOURCE) $(DEP_CPP_CLASS) "$(INTDIR)"\
 "$(INTDIR)\Feature.pch"


!ELSEIF  "$(CFG)" == "Feature - Win32 Debug"


"$(INTDIR)\Classdlg.obj" : $(SOURCE) $(DEP_CPP_CLASS) "$(INTDIR)"\
 "$(INTDIR)\Feature.pch"

"$(INTDIR)\Classdlg.sbr" : $(SOURCE) $(DEP_CPP_CLASS) "$(INTDIR)"\
 "$(INTDIR)\Feature.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Cgobject.cxx
DEP_CPP_CGOBJ=\
	".\CGOBJECT.HXX"\
	".\FEATURE.HXX"\
	".\Featurep.hxx"\
	".\UIDOBJ.HXX"\
	".\UIDOBJ.INL"\
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
	{$(INCLUDE)}"\Eieruhr.hxx"\
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
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
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
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\stdexcept"\
	{$(INCLUDE)}"\STRDUPX.HXX"\
	{$(INCLUDE)}"\streambuf"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\typeinfo"\
	{$(INCLUDE)}"\use_ansi.h"\
	{$(INCLUDE)}"\utility"\
	{$(INCLUDE)}"\VERSIONS.H"\
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
	

!IF  "$(CFG)" == "Feature - Win32 Release"


"$(INTDIR)\Cgobject.obj" : $(SOURCE) $(DEP_CPP_CGOBJ) "$(INTDIR)"\
 "$(INTDIR)\Feature.pch"


!ELSEIF  "$(CFG)" == "Feature - Win32 Debug"


"$(INTDIR)\Cgobject.obj" : $(SOURCE) $(DEP_CPP_CGOBJ) "$(INTDIR)"\
 "$(INTDIR)\Feature.pch"

"$(INTDIR)\Cgobject.sbr" : $(SOURCE) $(DEP_CPP_CGOBJ) "$(INTDIR)"\
 "$(INTDIR)\Feature.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Merkmal.def

!IF  "$(CFG)" == "Feature - Win32 Release"

!ELSEIF  "$(CFG)" == "Feature - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
