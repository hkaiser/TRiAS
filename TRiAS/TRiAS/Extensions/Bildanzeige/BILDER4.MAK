# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Bilder - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Bilder - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Bilder - Win32 Release" && "$(CFG)" != "Bilder - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "BILDER4.MAK" CFG="Bilder - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Bilder - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Bilder - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "Bilder - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "Bilder - Win32 Release"

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
TargetName=bilder
# End Custom Macros

ALL : "$(OUTDIR)\bilder.ext" "c:\trias.mvc\trias200.rel\bilder.ext"

CLEAN : 
	-@erase "$(INTDIR)\BILDER.OBJ"
	-@erase "$(INTDIR)\Bilder32.res"
	-@erase "$(INTDIR)\BILDER4.pch"
	-@erase "$(INTDIR)\BILDERP.OBJ"
	-@erase "$(INTDIR)\BILDOBJ.OBJ"
	-@erase "$(INTDIR)\BILDPROF.OBJ"
	-@erase "$(INTDIR)\BILDWIND.OBJ"
	-@erase "$(INTDIR)\MINMAXWD.OBJ"
	-@erase "$(OUTDIR)\bilder.exp"
	-@erase "$(OUTDIR)\bilder.ext"
	-@erase "$(OUTDIR)\bilder.lib"
	-@erase "c:\trias.mvc\trias200.rel\bilder.ext"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/BILDER.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "MSWIND" /D "DLL" /D "__CV__" /D "__XTENSNDLL__" /D "__XT" /D "__DEXPROCS" /Yu"bilderp.hxx" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "MSWIND" /D "DLL" /D "__CV__" /D "__XTENSNDLL__" /D "__XT" /D\
 "__DEXPROCS" /Fp"$(INTDIR)/BILDER4.pch" /Yu"bilderp.hxx" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /i ".." /d "NDEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/Bilder32.res" /i ".." /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/BILDER4.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ixtnsr40.lib stdcppr.lib tfrmwork.lib cont32r.lib lz32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /stub:"obj32/rights.exe" /out:"Release/bilder.ext" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=ixtnsr40.lib stdcppr.lib tfrmwork.lib cont32r.lib lz32.lib\
 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib\
 shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo\
 /dll /incremental:no /pdb:"$(OUTDIR)/bilder.pdb" /machine:I386\
 /def:".\OBJ32\BILDER32.DEF" /stub:"obj32/rights.exe"\
 /out:"$(OUTDIR)/bilder.ext" /implib:"$(OUTDIR)/bilder.lib"\
 /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\OBJ32\BILDER32.DEF"
LINK32_OBJS= \
	"$(INTDIR)\BILDER.OBJ" \
	"$(INTDIR)\Bilder32.res" \
	"$(INTDIR)\BILDERP.OBJ" \
	"$(INTDIR)\BILDOBJ.OBJ" \
	"$(INTDIR)\BILDPROF.OBJ" \
	"$(INTDIR)\BILDWIND.OBJ" \
	"$(INTDIR)\MINMAXWD.OBJ"

"$(OUTDIR)\bilder.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
TargetPath=.\Release\bilder.ext
TargetName=bilder
InputPath=.\Release\bilder.ext
SOURCE=$(InputPath)

"c:\trias.mvc\trias200.rel\$(TargetName).ext" : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
   copy "$(TargetPath)" c:\trias.mvc\trias200.rel

# End Custom Build

!ELSEIF  "$(CFG)" == "Bilder - Win32 Debug"

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
TargetName=bilderd
# End Custom Macros

ALL : "$(OUTDIR)\bilderd.ext" "c:\trias.mvc\trias200\bilderd.ext"

CLEAN : 
	-@erase "$(INTDIR)\BILDER.OBJ"
	-@erase "$(INTDIR)\Bilder32.res"
	-@erase "$(INTDIR)\BILDERd.idb"
	-@erase "$(INTDIR)\BILDERd.pch"
	-@erase "$(INTDIR)\BILDERd.pdb"
	-@erase "$(INTDIR)\BILDERP.OBJ"
	-@erase "$(INTDIR)\BILDOBJ.OBJ"
	-@erase "$(INTDIR)\BILDPROF.OBJ"
	-@erase "$(INTDIR)\BILDWIND.OBJ"
	-@erase "$(INTDIR)\MINMAXWD.OBJ"
	-@erase "$(OUTDIR)\bilderd.exp"
	-@erase "$(OUTDIR)\bilderd.ext"
	-@erase "$(OUTDIR)\bilderd.ilk"
	-@erase "$(OUTDIR)\bilderd.lib"
	-@erase "c:\trias.mvc\trias200\bilderd.ext"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/BILDER.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "MSWIND" /D "DLL" /D "__CV__" /D "__XTENSNDLL__" /D "__XT" /D "__DEXPROCS" /Fp"Debug/BILDERd.pch" /Yu"bilderp.hxx" /Fd"Debug/BILDERd.pdb" /c
CPP_PROJ=/nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "MSWIND" /D "DLL" /D "__CV__" /D "__XTENSNDLL__" /D\
 "__XT" /D "__DEXPROCS" /Fp"$(INTDIR)/BILDERd.pch" /Yu"bilderp.hxx"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/BILDERd.pdb" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /i ".." /d "_DEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/Bilder32.res" /i ".." /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/BILDER4.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 ixtnsd42.lib stdcppd.lib tfrm32d.lib cont32d.lib lz32.lib kernel32.lib user32.lib gdi32.lib advapi32.lib oleaut32.lib uuid.lib ole32.lib /nologo /dll /debug /machine:I386 /stub:"obj32/rights.exe" /out:"Debug/bilderd.ext" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=ixtnsd42.lib stdcppd.lib tfrm32d.lib cont32d.lib lz32.lib\
 kernel32.lib user32.lib gdi32.lib advapi32.lib oleaut32.lib uuid.lib ole32.lib\
 /nologo /dll /incremental:yes /pdb:"$(OUTDIR)/bilderd.pdb" /debug /machine:I386\
 /def:".\OBJ32\BILDER32.DEF" /stub:"obj32/rights.exe"\
 /out:"$(OUTDIR)/bilderd.ext" /implib:"$(OUTDIR)/bilderd.lib"\
 /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\OBJ32\BILDER32.DEF"
LINK32_OBJS= \
	"$(INTDIR)\BILDER.OBJ" \
	"$(INTDIR)\Bilder32.res" \
	"$(INTDIR)\BILDERP.OBJ" \
	"$(INTDIR)\BILDOBJ.OBJ" \
	"$(INTDIR)\BILDPROF.OBJ" \
	"$(INTDIR)\BILDWIND.OBJ" \
	"$(INTDIR)\MINMAXWD.OBJ"

"$(OUTDIR)\bilderd.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
TargetPath=.\Debug\bilderd.ext
TargetName=bilderd
InputPath=.\Debug\bilderd.ext
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

# Name "Bilder - Win32 Release"
# Name "Bilder - Win32 Debug"

!IF  "$(CFG)" == "Bilder - Win32 Release"

!ELSEIF  "$(CFG)" == "Bilder - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\BILDWIND.CXX
DEP_CPP_BILDW=\
	".\bilderp.hxx"\
	".\bildobj.hxx"\
	".\bildwind.hxx"\
	".\minmaxwd.hxx"\
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
	

"$(INTDIR)\BILDWIND.OBJ" : $(SOURCE) $(DEP_CPP_BILDW) "$(INTDIR)"\
 "$(INTDIR)\BILDER4.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\BILDPROF.CXX
DEP_CPP_BILDP=\
	".\bilderp.hxx"\
	".\bildobj.hxx"\
	".\bildprof.hxx"\
	".\bildwind.hxx"\
	".\minmaxwd.hxx"\
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
	

"$(INTDIR)\BILDPROF.OBJ" : $(SOURCE) $(DEP_CPP_BILDP) "$(INTDIR)"\
 "$(INTDIR)\BILDER4.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MINMAXWD.CXX
DEP_CPP_MINMA=\
	".\bilderp.hxx"\
	".\bildobj.hxx"\
	".\bildwind.hxx"\
	".\minmaxwd.hxx"\
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
	

"$(INTDIR)\MINMAXWD.OBJ" : $(SOURCE) $(DEP_CPP_MINMA) "$(INTDIR)"\
 "$(INTDIR)\BILDER4.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\BILDOBJ.CXX
DEP_CPP_BILDO=\
	".\bilderp.hxx"\
	".\bildobj.hxx"\
	".\bildwind.hxx"\
	".\minmaxwd.hxx"\
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
	

"$(INTDIR)\BILDOBJ.OBJ" : $(SOURCE) $(DEP_CPP_BILDO) "$(INTDIR)"\
 "$(INTDIR)\BILDER4.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\BILDER.CXX
DEP_CPP_BILDE=\
	".\bilder.hxx"\
	".\bilderp.hxx"\
	".\bilderr.h"\
	".\bildguid.h"\
	".\bildobj.hxx"\
	".\bildprof.hxx"\
	".\bildwind.hxx"\
	".\minmaxwd.hxx"\
	".\obj32\versio32.h"\
	".\versio16.h"\
	".\version.h"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	
NODEP_CPP_BILDE=\
	".\bilder.h"\
	

"$(INTDIR)\BILDER.OBJ" : $(SOURCE) $(DEP_CPP_BILDE) "$(INTDIR)"\
 "$(INTDIR)\BILDER4.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\BILDERP.CXX
DEP_CPP_BILDER=\
	".\bilderp.hxx"\
	".\bildobj.hxx"\
	".\bildwind.hxx"\
	".\minmaxwd.hxx"\
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
	

!IF  "$(CFG)" == "Bilder - Win32 Release"

# ADD CPP /Yc"bilderp.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "MSWIND" /D "DLL" /D "__CV__" /D "__XTENSNDLL__" /D "__XT" /D\
 "__DEXPROCS" /Fp"$(INTDIR)/BILDER4.pch" /Yc"bilderp.hxx" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\BILDERP.OBJ" : $(SOURCE) $(DEP_CPP_BILDER) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\BILDER4.pch" : $(SOURCE) $(DEP_CPP_BILDER) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Bilder - Win32 Debug"

# ADD CPP /Yc"bilderp.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "MSWIND" /D "DLL" /D "__CV__" /D "__XTENSNDLL__" /D\
 "__XT" /D "__DEXPROCS" /Fp"$(INTDIR)/BILDERd.pch" /Yc"bilderp.hxx"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/BILDERd.pdb" /c $(SOURCE) \
	

"$(INTDIR)\BILDERP.OBJ" : $(SOURCE) $(DEP_CPP_BILDER) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\BILDERd.pch" : $(SOURCE) $(DEP_CPP_BILDER) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OBJ32\BILDER32.DEF

!IF  "$(CFG)" == "Bilder - Win32 Release"

!ELSEIF  "$(CFG)" == "Bilder - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OBJ32\Bilder32.rc
DEP_RSC_BILDER3=\
	".\OBJ32\bilder32.rcv"\
	{$(INCLUDE)}"\RESSTRG.H"\
	

!IF  "$(CFG)" == "Bilder - Win32 Release"


"$(INTDIR)\Bilder32.res" : $(SOURCE) $(DEP_RSC_BILDER3) "$(INTDIR)"
   $(RSC) /l 0x407 /fo"$(INTDIR)/Bilder32.res" /i ".." /i "OBJ32" /d "NDEBUG"\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "Bilder - Win32 Debug"


"$(INTDIR)\Bilder32.res" : $(SOURCE) $(DEP_RSC_BILDER3) "$(INTDIR)"
   $(RSC) /l 0x407 /fo"$(INTDIR)/Bilder32.res" /i ".." /i "OBJ32" /d "_DEBUG"\
 $(SOURCE)


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
