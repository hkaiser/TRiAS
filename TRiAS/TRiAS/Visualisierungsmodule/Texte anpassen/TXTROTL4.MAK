# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=txtrotl - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to txtrotl - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "txtrotl - Win32 Release" && "$(CFG)" !=\
 "txtrotl - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "TXTROTL4.MAK" CFG="txtrotl - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "txtrotl - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "txtrotl - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "txtrotl - Win32 Debug"
CPP=cl.exe
MTL=mktyplib.exe
RSC=rc.exe

!IF  "$(CFG)" == "txtrotl - Win32 Release"

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
TargetName=txtrotl
# End Custom Macros

ALL : "$(OUTDIR)\txtrotl.vmd" "c:\trias.mvc\trias200.rel\txtrotl.vmd"

CLEAN : 
	-@erase "$(INTDIR)\DCUSTVIS.OBJ"
	-@erase "$(INTDIR)\Dumpout.obj"
	-@erase "$(INTDIR)\ITXTROTL.OBJ"
	-@erase "$(INTDIR)\Regvism.obj"
	-@erase "$(INTDIR)\txtrotl.res"
	-@erase "$(INTDIR)\TXTROTL4.pch"
	-@erase "$(INTDIR)\TXTROTLP.OBJ"
	-@erase "$(OUTDIR)\txtrotl.exp"
	-@erase "$(OUTDIR)\txtrotl.lib"
	-@erase "$(OUTDIR)\txtrotl.vmd"
	-@erase "c:\trias.mvc\trias200.rel\txtrotl.vmd"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/txtrotl.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /O2 /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "MSWIND" /D "__XT" /D "DLL" /D "__DEXPROCS" /D "__CV__" /D "__VMD_DLL__" /Yu"txtrotlp.hxx" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /WX /GX /O2 /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "MSWIND" /D "__XT" /D "DLL" /D "__DEXPROCS" /D "__CV__" /D\
 "__VMD_DLL__" /Fp"$(INTDIR)/TXTROTL4.pch" /Yu"txtrotlp.hxx" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/txtrotl.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/TXTROTL4.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 stdcppr.lib tfrmwork.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /stub:"Obj32/rights.exe" /out:"Release/txtrotl.vmd" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=stdcppr.lib tfrmwork.lib kernel32.lib user32.lib gdi32.lib\
 winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib\
 uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no\
 /pdb:"$(OUTDIR)/txtrotl.pdb" /machine:I386 /def:".\obj32\TXTROT32.DEF"\
 /stub:"Obj32/rights.exe" /out:"$(OUTDIR)/txtrotl.vmd"\
 /implib:"$(OUTDIR)/txtrotl.lib" /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\obj32\TXTROT32.DEF"
LINK32_OBJS= \
	"$(INTDIR)\DCUSTVIS.OBJ" \
	"$(INTDIR)\Dumpout.obj" \
	"$(INTDIR)\ITXTROTL.OBJ" \
	"$(INTDIR)\Regvism.obj" \
	"$(INTDIR)\txtrotl.res" \
	"$(INTDIR)\TXTROTLP.OBJ"

"$(OUTDIR)\txtrotl.vmd" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
TargetPath=.\Release\txtrotl.vmd
TargetName=txtrotl
InputPath=.\Release\txtrotl.vmd
SOURCE=$(InputPath)

"c:\trias.mvc\trias200.rel\$(TargetName).vmd" : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
   copy "$(TargetPath)" c:\trias.mvc\trias200.rel

# End Custom Build

!ELSEIF  "$(CFG)" == "txtrotl - Win32 Debug"

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
TargetName=txtrotl
# End Custom Macros

ALL : "$(OUTDIR)\txtrotl.vmd" "$(OUTDIR)\TXTROTL4.bsc"\
 "c:\trias.mvc\trias200\txtrotl.vmd"

CLEAN : 
	-@erase "$(INTDIR)\DCUSTVIS.OBJ"
	-@erase "$(INTDIR)\DCUSTVIS.SBR"
	-@erase "$(INTDIR)\Dumpout.obj"
	-@erase "$(INTDIR)\Dumpout.sbr"
	-@erase "$(INTDIR)\ITXTROTL.OBJ"
	-@erase "$(INTDIR)\ITXTROTL.SBR"
	-@erase "$(INTDIR)\Regvism.obj"
	-@erase "$(INTDIR)\Regvism.sbr"
	-@erase "$(INTDIR)\txtrotl.res"
	-@erase "$(INTDIR)\txtrotld.idb"
	-@erase "$(INTDIR)\txtrotld.pch"
	-@erase "$(INTDIR)\txtrotld.pdb"
	-@erase "$(INTDIR)\TXTROTLP.OBJ"
	-@erase "$(INTDIR)\TXTROTLP.SBR"
	-@erase "$(OUTDIR)\txtrotl.exp"
	-@erase "$(OUTDIR)\txtrotl.ilk"
	-@erase "$(OUTDIR)\txtrotl.lib"
	-@erase "$(OUTDIR)\txtrotl.pdb"
	-@erase "$(OUTDIR)\txtrotl.vmd"
	-@erase "$(OUTDIR)\TXTROTL4.bsc"
	-@erase "c:\trias.mvc\trias200\txtrotl.vmd"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/txtrotl.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "MSWIND" /D "__XT" /D "DLL" /D "__DEXPROCS" /D "__CV__" /D "__VMD_DLL__" /FR /Fp"Debug/txtrotld.pch" /Yu"txtrotlp.hxx" /Fd"Debug/txtrotld.pdb" /c
CPP_PROJ=/nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "MSWIND" /D "__XT" /D "DLL" /D "__DEXPROCS" /D\
 "__CV__" /D "__VMD_DLL__" /FR"$(INTDIR)/" /Fp"$(INTDIR)/txtrotld.pch"\
 /Yu"txtrotlp.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/txtrotld.pdb" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/txtrotl.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/TXTROTL4.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\DCUSTVIS.SBR" \
	"$(INTDIR)\Dumpout.sbr" \
	"$(INTDIR)\ITXTROTL.SBR" \
	"$(INTDIR)\Regvism.sbr" \
	"$(INTDIR)\TXTROTLP.SBR"

"$(OUTDIR)\TXTROTL4.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 stdcppd.lib tfrm32d.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /stub:"Obj32/rights.exe" /out:"Debug/txtrotl.vmd" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=stdcppd.lib tfrm32d.lib kernel32.lib user32.lib gdi32.lib\
 winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib\
 uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes\
 /pdb:"$(OUTDIR)/txtrotl.pdb" /debug /machine:I386 /def:".\obj32\TXTROT32.DEF"\
 /stub:"Obj32/rights.exe" /out:"$(OUTDIR)/txtrotl.vmd"\
 /implib:"$(OUTDIR)/txtrotl.lib" /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\obj32\TXTROT32.DEF"
LINK32_OBJS= \
	"$(INTDIR)\DCUSTVIS.OBJ" \
	"$(INTDIR)\Dumpout.obj" \
	"$(INTDIR)\ITXTROTL.OBJ" \
	"$(INTDIR)\Regvism.obj" \
	"$(INTDIR)\txtrotl.res" \
	"$(INTDIR)\TXTROTLP.OBJ"

"$(OUTDIR)\txtrotl.vmd" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
TargetPath=.\Debug\txtrotl.vmd
TargetName=txtrotl
InputPath=.\Debug\txtrotl.vmd
SOURCE=$(InputPath)

"c:\trias.mvc\trias200\$(TargetName).vmd" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
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

# Name "txtrotl - Win32 Release"
# Name "txtrotl - Win32 Debug"

!IF  "$(CFG)" == "txtrotl - Win32 Release"

!ELSEIF  "$(CFG)" == "txtrotl - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ITXTROTL.CXX

!IF  "$(CFG)" == "txtrotl - Win32 Release"

DEP_CPP_ITXTR=\
	".\itxtrotl.hxx"\
	".\TXTROTL.H"\
	".\txtrotlp.hxx"\
	{$(INCLUDE)}"\Icustom.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\vismguid.h"\
	

"$(INTDIR)\ITXTROTL.OBJ" : $(SOURCE) $(DEP_CPP_ITXTR) "$(INTDIR)"\
 "$(INTDIR)\TXTROTL4.pch"


!ELSEIF  "$(CFG)" == "txtrotl - Win32 Debug"

DEP_CPP_ITXTR=\
	".\itxtrotl.hxx"\
	".\TXTROTL.H"\
	".\txtrotlp.hxx"\
	{$(INCLUDE)}"\Icustom.hxx"\
	{$(INCLUDE)}"\vismguid.h"\
	

"$(INTDIR)\ITXTROTL.OBJ" : $(SOURCE) $(DEP_CPP_ITXTR) "$(INTDIR)"\
 "$(INTDIR)\txtrotld.pch"

"$(INTDIR)\ITXTROTL.SBR" : $(SOURCE) $(DEP_CPP_ITXTR) "$(INTDIR)"\
 "$(INTDIR)\txtrotld.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DCUSTVIS.CXX
DEP_CPP_DCUST=\
	".\dcustvis.hxx"\
	".\itxtrotl.hxx"\
	".\TXTROTL.H"\
	".\txtrotlp.hxx"\
	".\txtrotlr.h"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\exception"\
	{$(INCLUDE)}"\Icustom.hxx"\
	{$(INCLUDE)}"\ios"\
	{$(INCLUDE)}"\iosfwd"\
	{$(INCLUDE)}"\istream"\
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
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\stdexcept"\
	{$(INCLUDE)}"\streambuf"\
	{$(INCLUDE)}"\string"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\typeinfo"\
	{$(INCLUDE)}"\use_ansi.h"\
	{$(INCLUDE)}"\utility"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\vismguid.h"\
	{$(INCLUDE)}"\xiosbase"\
	{$(INCLUDE)}"\xlocale"\
	{$(INCLUDE)}"\xlocinfo"\
	{$(INCLUDE)}"\xlocinfo.h"\
	{$(INCLUDE)}"\xlocnum"\
	{$(INCLUDE)}"\xmemory"\
	{$(INCLUDE)}"\xstddef"\
	{$(INCLUDE)}"\xstring"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	

!IF  "$(CFG)" == "txtrotl - Win32 Release"


"$(INTDIR)\DCUSTVIS.OBJ" : $(SOURCE) $(DEP_CPP_DCUST) "$(INTDIR)"\
 "$(INTDIR)\TXTROTL4.pch"


!ELSEIF  "$(CFG)" == "txtrotl - Win32 Debug"


"$(INTDIR)\DCUSTVIS.OBJ" : $(SOURCE) $(DEP_CPP_DCUST) "$(INTDIR)"\
 "$(INTDIR)\txtrotld.pch"

"$(INTDIR)\DCUSTVIS.SBR" : $(SOURCE) $(DEP_CPP_DCUST) "$(INTDIR)"\
 "$(INTDIR)\txtrotld.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TXTROTLP.CXX
DEP_CPP_TXTRO=\
	".\txtrotlp.hxx"\
	{$(INCLUDE)}"\VMDM.HXX"\
	

!IF  "$(CFG)" == "txtrotl - Win32 Release"

# ADD CPP /Yc"txtrotlp.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O2 /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "MSWIND" /D "__XT" /D "DLL" /D "__DEXPROCS" /D "__CV__" /D\
 "__VMD_DLL__" /Fp"$(INTDIR)/TXTROTL4.pch" /Yc"txtrotlp.hxx" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\TXTROTLP.OBJ" : $(SOURCE) $(DEP_CPP_TXTRO) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\TXTROTL4.pch" : $(SOURCE) $(DEP_CPP_TXTRO) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "txtrotl - Win32 Debug"

# ADD CPP /Yc"txtrotlp.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "MSWIND" /D "__XT" /D "DLL" /D "__DEXPROCS" /D\
 "__CV__" /D "__VMD_DLL__" /FR"$(INTDIR)/" /Fp"$(INTDIR)/txtrotld.pch"\
 /Yc"txtrotlp.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/txtrotld.pdb" /c $(SOURCE) \
	

"$(INTDIR)\TXTROTLP.OBJ" : $(SOURCE) $(DEP_CPP_TXTRO) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\TXTROTLP.SBR" : $(SOURCE) $(DEP_CPP_TXTRO) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\txtrotld.pch" : $(SOURCE) $(DEP_CPP_TXTRO) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Regvism.cxx
DEP_CPP_REGVI=\
	".\TXTROTL.H"\
	".\txtrotlp.hxx"\
	".\txtrotlr.h"\
	{$(INCLUDE)}"\Dirisole.h"\
	

!IF  "$(CFG)" == "txtrotl - Win32 Release"


"$(INTDIR)\Regvism.obj" : $(SOURCE) $(DEP_CPP_REGVI) "$(INTDIR)"\
 "$(INTDIR)\TXTROTL4.pch"


!ELSEIF  "$(CFG)" == "txtrotl - Win32 Debug"


"$(INTDIR)\Regvism.obj" : $(SOURCE) $(DEP_CPP_REGVI) "$(INTDIR)"\
 "$(INTDIR)\txtrotld.pch"

"$(INTDIR)\Regvism.sbr" : $(SOURCE) $(DEP_CPP_REGVI) "$(INTDIR)"\
 "$(INTDIR)\txtrotld.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dumpout.cxx
DEP_CPP_DUMPO=\
	".\txtrotlp.hxx"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	

!IF  "$(CFG)" == "txtrotl - Win32 Release"


"$(INTDIR)\Dumpout.obj" : $(SOURCE) $(DEP_CPP_DUMPO) "$(INTDIR)"\
 "$(INTDIR)\TXTROTL4.pch"


!ELSEIF  "$(CFG)" == "txtrotl - Win32 Debug"


"$(INTDIR)\Dumpout.obj" : $(SOURCE) $(DEP_CPP_DUMPO) "$(INTDIR)"\
 "$(INTDIR)\txtrotld.pch"

"$(INTDIR)\Dumpout.sbr" : $(SOURCE) $(DEP_CPP_DUMPO) "$(INTDIR)"\
 "$(INTDIR)\txtrotld.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\obj32\TXTROT32.DEF

!IF  "$(CFG)" == "txtrotl - Win32 Release"

!ELSEIF  "$(CFG)" == "txtrotl - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\obj32\txtrotl.RC
DEP_RSC_TXTROT=\
	".\obj32\txtrot32.rcv"\
	".\obj32\txtrotl.h"\
	

!IF  "$(CFG)" == "txtrotl - Win32 Release"


"$(INTDIR)\txtrotl.res" : $(SOURCE) $(DEP_RSC_TXTROT) "$(INTDIR)"
   $(RSC) /l 0x407 /fo"$(INTDIR)/txtrotl.res" /i "obj32" /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "txtrotl - Win32 Debug"


"$(INTDIR)\txtrotl.res" : $(SOURCE) $(DEP_RSC_TXTROT) "$(INTDIR)"
   $(RSC) /l 0x407 /fo"$(INTDIR)/txtrotl.res" /i "obj32" /d "_DEBUG" $(SOURCE)


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
