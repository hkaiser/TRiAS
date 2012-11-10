# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=feature - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to feature - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "feature - Win32 Release" && "$(CFG)" !=\
 "feature - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "feature4.mak" CFG="feature - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "feature - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "feature - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "feature - Win32 Debug"
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "feature - Win32 Release"

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
TargetName=feature
# End Custom Macros

ALL : "$(OUTDIR)\feature.ext" "c:\trias.mvc\trias200\feature.ext"

CLEAN : 
	-@erase "$(INTDIR)\clsfyprp.obj"
	-@erase "$(INTDIR)\clspropb.obj"
	-@erase "$(INTDIR)\datahelp.obj"
	-@erase "$(INTDIR)\DATAOBJ.OBJ"
	-@erase "$(INTDIR)\dstobdlg.obj"
	-@erase "$(INTDIR)\dstobwnd.obj"
	-@erase "$(INTDIR)\enumonr.obj"
	-@erase "$(INTDIR)\fclassfy.obj"
	-@erase "$(INTDIR)\FEATURE.res"
	-@erase "$(INTDIR)\feature4.pch"
	-@erase "$(INTDIR)\FEATUREP.OBJ"
	-@erase "$(INTDIR)\featurex.obj"
	-@erase "$(INTDIR)\IDATAOBJ.OBJ"
	-@erase "$(INTDIR)\IENUMFE.OBJ"
	-@erase "$(INTDIR)\propactb.obj"
	-@erase "$(INTDIR)\propname.obj"
	-@erase "$(INTDIR)\propseq.obj"
	-@erase "$(INTDIR)\selident.obj"
	-@erase "$(INTDIR)\selidlst.obj"
	-@erase "$(INTDIR)\selidpbd.obj"
	-@erase "$(INTDIR)\selidprp.obj"
	-@erase "$(INTDIR)\selobdlg.obj"
	-@erase "$(INTDIR)\selobwnd.obj"
	-@erase "$(INTDIR)\seloprop.obj"
	-@erase "$(INTDIR)\seloprpt.obj"
	-@erase "$(INTDIR)\selrcode.obj"
	-@erase "$(INTDIR)\selrelst.obj"
	-@erase "$(INTDIR)\selrlprp.obj"
	-@erase "$(OUTDIR)\feature.exp"
	-@erase "$(OUTDIR)\feature.ext"
	-@erase "$(OUTDIR)\feature.lib"
	-@erase "c:\trias.mvc\trias200\feature.ext"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/feature.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "__CV__" /D "MSWIND" /D "STRICT" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "NOMINMAX" /D "OS_ALTERNATIVE_STRING_NAMES" /Yu"featurep.hxx" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "__CV__" /D "MSWIND" /D "STRICT" /D\
 "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "NOMINMAX" /D\
 "OS_ALTERNATIVE_STRING_NAMES" /Fp"$(INTDIR)/feature4.pch" /Yu"featurep.hxx"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/FEATURE.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/feature4.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ospacer.lib stdcppr.lib ixtnsr40.lib tfrm32.lib cont32.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"Release/feature.ext" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=ospacer.lib stdcppr.lib ixtnsr40.lib tfrm32.lib cont32.lib\
 winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)/feature.pdb"\
 /machine:I386 /def:".\FEATURE.DEF" /out:"$(OUTDIR)/feature.ext"\
 /implib:"$(OUTDIR)/feature.lib" /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\FEATURE.DEF"
LINK32_OBJS= \
	"$(INTDIR)\clsfyprp.obj" \
	"$(INTDIR)\clspropb.obj" \
	"$(INTDIR)\datahelp.obj" \
	"$(INTDIR)\DATAOBJ.OBJ" \
	"$(INTDIR)\dstobdlg.obj" \
	"$(INTDIR)\dstobwnd.obj" \
	"$(INTDIR)\enumonr.obj" \
	"$(INTDIR)\fclassfy.obj" \
	"$(INTDIR)\FEATURE.res" \
	"$(INTDIR)\FEATUREP.OBJ" \
	"$(INTDIR)\featurex.obj" \
	"$(INTDIR)\IDATAOBJ.OBJ" \
	"$(INTDIR)\IENUMFE.OBJ" \
	"$(INTDIR)\propactb.obj" \
	"$(INTDIR)\propname.obj" \
	"$(INTDIR)\propseq.obj" \
	"$(INTDIR)\selident.obj" \
	"$(INTDIR)\selidlst.obj" \
	"$(INTDIR)\selidpbd.obj" \
	"$(INTDIR)\selidprp.obj" \
	"$(INTDIR)\selobdlg.obj" \
	"$(INTDIR)\selobwnd.obj" \
	"$(INTDIR)\seloprop.obj" \
	"$(INTDIR)\seloprpt.obj" \
	"$(INTDIR)\selrcode.obj" \
	"$(INTDIR)\selrelst.obj" \
	"$(INTDIR)\selrlprp.obj"

"$(OUTDIR)\feature.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
TargetPath=.\Release\feature.ext
TargetName=feature
InputPath=.\Release\feature.ext
SOURCE=$(InputPath)

"c:\trias.mvc\trias200\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   copy "$(TargetPath)" c:\trias.mvc\trias200

# End Custom Build

!ELSEIF  "$(CFG)" == "feature - Win32 Debug"

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
TargetName=featured
# End Custom Macros

ALL : "$(OUTDIR)\featured.ext" "$(OUTDIR)\feature4.bsc"\
 "c:\trias.mvc\trias200\featured.ext"

CLEAN : 
	-@erase "$(INTDIR)\clsfyprp.obj"
	-@erase "$(INTDIR)\clsfyprp.sbr"
	-@erase "$(INTDIR)\clspropb.obj"
	-@erase "$(INTDIR)\clspropb.sbr"
	-@erase "$(INTDIR)\datahelp.obj"
	-@erase "$(INTDIR)\datahelp.sbr"
	-@erase "$(INTDIR)\DATAOBJ.OBJ"
	-@erase "$(INTDIR)\DATAOBJ.SBR"
	-@erase "$(INTDIR)\dstobdlg.obj"
	-@erase "$(INTDIR)\dstobdlg.sbr"
	-@erase "$(INTDIR)\dstobwnd.obj"
	-@erase "$(INTDIR)\dstobwnd.sbr"
	-@erase "$(INTDIR)\enumonr.obj"
	-@erase "$(INTDIR)\enumonr.sbr"
	-@erase "$(INTDIR)\fclassfy.obj"
	-@erase "$(INTDIR)\fclassfy.sbr"
	-@erase "$(INTDIR)\FEATURE.res"
	-@erase "$(INTDIR)\featured.pch"
	-@erase "$(INTDIR)\featured.pdb"
	-@erase "$(INTDIR)\FEATUREP.OBJ"
	-@erase "$(INTDIR)\FEATUREP.SBR"
	-@erase "$(INTDIR)\featurex.obj"
	-@erase "$(INTDIR)\featurex.sbr"
	-@erase "$(INTDIR)\IDATAOBJ.OBJ"
	-@erase "$(INTDIR)\IDATAOBJ.SBR"
	-@erase "$(INTDIR)\IENUMFE.OBJ"
	-@erase "$(INTDIR)\IENUMFE.SBR"
	-@erase "$(INTDIR)\propactb.obj"
	-@erase "$(INTDIR)\propactb.sbr"
	-@erase "$(INTDIR)\propname.obj"
	-@erase "$(INTDIR)\propname.sbr"
	-@erase "$(INTDIR)\propseq.obj"
	-@erase "$(INTDIR)\propseq.sbr"
	-@erase "$(INTDIR)\selident.obj"
	-@erase "$(INTDIR)\selident.sbr"
	-@erase "$(INTDIR)\selidlst.obj"
	-@erase "$(INTDIR)\selidlst.sbr"
	-@erase "$(INTDIR)\selidpbd.obj"
	-@erase "$(INTDIR)\selidpbd.sbr"
	-@erase "$(INTDIR)\selidprp.obj"
	-@erase "$(INTDIR)\selidprp.sbr"
	-@erase "$(INTDIR)\selobdlg.obj"
	-@erase "$(INTDIR)\selobdlg.sbr"
	-@erase "$(INTDIR)\selobwnd.obj"
	-@erase "$(INTDIR)\selobwnd.sbr"
	-@erase "$(INTDIR)\seloprop.obj"
	-@erase "$(INTDIR)\seloprop.sbr"
	-@erase "$(INTDIR)\seloprpt.obj"
	-@erase "$(INTDIR)\seloprpt.sbr"
	-@erase "$(INTDIR)\selrcode.obj"
	-@erase "$(INTDIR)\selrcode.sbr"
	-@erase "$(INTDIR)\selrelst.obj"
	-@erase "$(INTDIR)\selrelst.sbr"
	-@erase "$(INTDIR)\selrlprp.obj"
	-@erase "$(INTDIR)\selrlprp.sbr"
	-@erase "$(OUTDIR)\feature4.bsc"
	-@erase "$(OUTDIR)\featured.exp"
	-@erase "$(OUTDIR)\featured.ext"
	-@erase "$(OUTDIR)\featured.ilk"
	-@erase "$(OUTDIR)\featured.lib"
	-@erase "c:\trias.mvc\trias200\featured.ext"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/feature.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "__CV__" /D "MSWIND" /D "STRICT" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "NOMINMAX" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /FR /Fp"Debug/featured.pch" /Yu"featurep.hxx" /Fd"Debug/featured.pdb" /c
CPP_PROJ=/nologo /MDd /W3 /WX /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "__CV__" /D "MSWIND"\
 /D "STRICT" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "NOMINMAX"\
 /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/featured.pch" /Yu"featurep.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/featured.pdb" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/FEATURE.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/feature4.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\clsfyprp.sbr" \
	"$(INTDIR)\clspropb.sbr" \
	"$(INTDIR)\datahelp.sbr" \
	"$(INTDIR)\DATAOBJ.SBR" \
	"$(INTDIR)\dstobdlg.sbr" \
	"$(INTDIR)\dstobwnd.sbr" \
	"$(INTDIR)\enumonr.sbr" \
	"$(INTDIR)\fclassfy.sbr" \
	"$(INTDIR)\FEATUREP.SBR" \
	"$(INTDIR)\featurex.sbr" \
	"$(INTDIR)\IDATAOBJ.SBR" \
	"$(INTDIR)\IENUMFE.SBR" \
	"$(INTDIR)\propactb.sbr" \
	"$(INTDIR)\propname.sbr" \
	"$(INTDIR)\propseq.sbr" \
	"$(INTDIR)\selident.sbr" \
	"$(INTDIR)\selidlst.sbr" \
	"$(INTDIR)\selidpbd.sbr" \
	"$(INTDIR)\selidprp.sbr" \
	"$(INTDIR)\selobdlg.sbr" \
	"$(INTDIR)\selobwnd.sbr" \
	"$(INTDIR)\seloprop.sbr" \
	"$(INTDIR)\seloprpt.sbr" \
	"$(INTDIR)\selrcode.sbr" \
	"$(INTDIR)\selrelst.sbr" \
	"$(INTDIR)\selrlprp.sbr"

"$(OUTDIR)\feature4.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 ospaced.lib stdcppd.lib ixtnsd40.lib cont32d.lib tfrm32d.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"Debug/featured.ext" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none /force
LINK32_FLAGS=ospaced.lib stdcppd.lib ixtnsd40.lib cont32d.lib tfrm32d.lib\
 winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)/featured.pdb" /debug\
 /machine:I386 /def:".\FEATURE.DEF" /out:"$(OUTDIR)/featured.ext"\
 /implib:"$(OUTDIR)/featured.lib" /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\FEATURE.DEF"
LINK32_OBJS= \
	"$(INTDIR)\clsfyprp.obj" \
	"$(INTDIR)\clspropb.obj" \
	"$(INTDIR)\datahelp.obj" \
	"$(INTDIR)\DATAOBJ.OBJ" \
	"$(INTDIR)\dstobdlg.obj" \
	"$(INTDIR)\dstobwnd.obj" \
	"$(INTDIR)\enumonr.obj" \
	"$(INTDIR)\fclassfy.obj" \
	"$(INTDIR)\FEATURE.res" \
	"$(INTDIR)\FEATUREP.OBJ" \
	"$(INTDIR)\featurex.obj" \
	"$(INTDIR)\IDATAOBJ.OBJ" \
	"$(INTDIR)\IENUMFE.OBJ" \
	"$(INTDIR)\propactb.obj" \
	"$(INTDIR)\propname.obj" \
	"$(INTDIR)\propseq.obj" \
	"$(INTDIR)\selident.obj" \
	"$(INTDIR)\selidlst.obj" \
	"$(INTDIR)\selidpbd.obj" \
	"$(INTDIR)\selidprp.obj" \
	"$(INTDIR)\selobdlg.obj" \
	"$(INTDIR)\selobwnd.obj" \
	"$(INTDIR)\seloprop.obj" \
	"$(INTDIR)\seloprpt.obj" \
	"$(INTDIR)\selrcode.obj" \
	"$(INTDIR)\selrelst.obj" \
	"$(INTDIR)\selrlprp.obj"

"$(OUTDIR)\featured.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
TargetPath=.\Debug\featured.ext
TargetName=featured
InputPath=.\Debug\featured.ext
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

# Name "feature - Win32 Release"
# Name "feature - Win32 Debug"

!IF  "$(CFG)" == "feature - Win32 Release"

!ELSEIF  "$(CFG)" == "feature - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\FEATURE.RC
DEP_RSC_FEATU=\
	".\FEATURE.RCV"\
	

"$(INTDIR)\FEATURE.res" : $(SOURCE) $(DEP_RSC_FEATU) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\FEATURE\featurex.cxx

!IF  "$(CFG)" == "feature - Win32 Release"

DEP_CPP_FEATUR=\
	".\..\clsfyprp.hxx"\
	".\..\clspropb.hxx"\
	".\..\dstobwnd.hxx"\
	".\..\enumonr.hxx"\
	".\..\FEATGUID.H"\
	".\..\FEATURE.H"\
	".\..\feature.hxx"\
	".\..\FEATUREP.HXX"\
	".\..\propactb.hxx"\
	".\..\selidprp.hxx"\
	".\..\selobwnd.hxx"\
	".\..\selrlprp.hxx"\
	".\..\VERSION.H"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
	{$(INCLUDE)}"\clsfyprp.h"\
	{$(INCLUDE)}"\cstddef"\
	{$(INCLUDE)}"\cstdio"\
	{$(INCLUDE)}"\cstdlib"\
	{$(INCLUDE)}"\cstring"\
	{$(INCLUDE)}"\cwchar"\
	{$(INCLUDE)}"\dstobwnd.h"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\exception"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\ios"\
	{$(INCLUDE)}"\iosfwd"\
	{$(INCLUDE)}"\Ipropseq.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ixtensnw.hxx"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\oprpguid.h"\
	{$(INCLUDE)}"\OSPACE\CONFIG.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\BC45.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\COMPILER.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HP3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HPGNU270.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\LOCAL.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\MS20.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\PLATFORM.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGIDCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGINCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN4.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS\Errors.h"\
	{$(INCLUDE)}"\OSPACE\THREADS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\AUTOLOCK.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\COUNTING.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\EVENT.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.CC"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MUTEX.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THISTHRD.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THREAD.H"\
	{$(INCLUDE)}"\OSPACE\TYPES.H"\
	{$(INCLUDE)}"\OSPACE\TYPES\Types.h"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\Selidprp.h"\
	{$(INCLUDE)}"\selobwnd.h"\
	{$(INCLUDE)}"\selrlprp.h"\
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
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\xtsnprop.hxx"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	
NODEP_CPP_FEATUR=\
	".\..\versio16.h"\
	

"$(INTDIR)\featurex.obj" : $(SOURCE) $(DEP_CPP_FEATUR) "$(INTDIR)"\
 "$(INTDIR)\feature4.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "feature - Win32 Debug"

DEP_CPP_FEATUR=\
	".\..\clsfyprp.hxx"\
	".\..\clspropb.hxx"\
	".\..\dstobwnd.hxx"\
	".\..\FEATGUID.H"\
	".\..\FEATURE.H"\
	".\..\FEATUREP.HXX"\
	".\..\propactb.hxx"\
	".\..\selidprp.hxx"\
	".\..\selobwnd.hxx"\
	".\..\selrlprp.hxx"\
	".\..\VERSION.H"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\clsfyprp.h"\
	{$(INCLUDE)}"\dstobwnd.h"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\oprpguid.h"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\Selidprp.h"\
	{$(INCLUDE)}"\selobwnd.h"\
	{$(INCLUDE)}"\selrlprp.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\use_ansi.h"\
	
NODEP_CPP_FEATUR=\
	".\..\versio16.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\featurex.obj" : $(SOURCE) $(DEP_CPP_FEATUR) "$(INTDIR)"\
 "$(INTDIR)\featured.pch"
   $(BuildCmds)

"$(INTDIR)\featurex.sbr" : $(SOURCE) $(DEP_CPP_FEATUR) "$(INTDIR)"\
 "$(INTDIR)\featured.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\FEATURE\FEATUREP.CXX

!IF  "$(CFG)" == "feature - Win32 Release"

DEP_CPP_FEATURE=\
	".\..\enumonr.hxx"\
	".\..\feature.hxx"\
	".\..\FEATUREP.HXX"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
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
	{$(INCLUDE)}"\Ipropseq.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ixtensnw.hxx"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\oprpguid.h"\
	{$(INCLUDE)}"\OSPACE\CONFIG.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\BC45.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\COMPILER.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HP3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HPGNU270.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\LOCAL.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\MS20.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\PLATFORM.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGIDCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGINCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN4.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS\Errors.h"\
	{$(INCLUDE)}"\OSPACE\THREADS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\AUTOLOCK.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\COUNTING.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\EVENT.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.CC"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MUTEX.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THISTHRD.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THREAD.H"\
	{$(INCLUDE)}"\OSPACE\TYPES.H"\
	{$(INCLUDE)}"\OSPACE\TYPES\Types.h"\
	{$(INCLUDE)}"\ostream"\
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
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\xtsnprop.hxx"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	
# ADD CPP /Yc"featurep.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "__CV__" /D "MSWIND" /D "STRICT" /D\
 "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "NOMINMAX" /D\
 "OS_ALTERNATIVE_STRING_NAMES" /Fp"$(INTDIR)/feature4.pch" /Yc"featurep.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\FEATUREP.OBJ" : $(SOURCE) $(DEP_CPP_FEATURE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\feature4.pch" : $(SOURCE) $(DEP_CPP_FEATURE) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "feature - Win32 Debug"

DEP_CPP_FEATURE=\
	".\..\FEATUREP.HXX"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\use_ansi.h"\
	
# ADD CPP /Yc"featurep.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "__CV__" /D "MSWIND"\
 /D "STRICT" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "NOMINMAX"\
 /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/featured.pch" /Yc"featurep.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/featured.pdb" /c $(SOURCE) \
	

"$(INTDIR)\FEATUREP.OBJ" : $(SOURCE) $(DEP_CPP_FEATURE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\FEATUREP.SBR" : $(SOURCE) $(DEP_CPP_FEATURE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\featured.pch" : $(SOURCE) $(DEP_CPP_FEATURE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FEATURE.DEF

!IF  "$(CFG)" == "feature - Win32 Release"

!ELSEIF  "$(CFG)" == "feature - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\FEATURE\fclassfy.cxx

!IF  "$(CFG)" == "feature - Win32 Release"

DEP_CPP_FCLAS=\
	".\..\enumonr.hxx"\
	".\..\FEATURE.H"\
	".\..\feature.hxx"\
	".\..\FEATUREP.HXX"\
	".\..\propseq.hxx"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
	{$(INCLUDE)}"\clsfyprp.h"\
	{$(INCLUDE)}"\cstddef"\
	{$(INCLUDE)}"\cstdio"\
	{$(INCLUDE)}"\cstdlib"\
	{$(INCLUDE)}"\cstring"\
	{$(INCLUDE)}"\cwchar"\
	{$(INCLUDE)}"\dstobwnd.h"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\exception"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\ios"\
	{$(INCLUDE)}"\iosfwd"\
	{$(INCLUDE)}"\Ipropseq.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ixtensnw.hxx"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\oprpguid.h"\
	{$(INCLUDE)}"\OSPACE\CONFIG.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\BC45.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\COMPILER.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HP3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HPGNU270.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\LOCAL.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\MS20.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\PLATFORM.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGIDCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGINCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN4.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS\Errors.h"\
	{$(INCLUDE)}"\OSPACE\THREADS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\AUTOLOCK.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\COUNTING.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\EVENT.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.CC"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MUTEX.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THISTHRD.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THREAD.H"\
	{$(INCLUDE)}"\OSPACE\TYPES.H"\
	{$(INCLUDE)}"\OSPACE\TYPES\Types.h"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\propguid.h"\
	{$(INCLUDE)}"\Selidprp.h"\
	{$(INCLUDE)}"\selobwnd.h"\
	{$(INCLUDE)}"\selrlprp.h"\
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
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\xtsnprop.hxx"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	

"$(INTDIR)\fclassfy.obj" : $(SOURCE) $(DEP_CPP_FCLAS) "$(INTDIR)"\
 "$(INTDIR)\feature4.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "feature - Win32 Debug"

DEP_CPP_FCLAS=\
	".\..\FEATURE.H"\
	".\..\FEATUREP.HXX"\
	".\..\propseq.hxx"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\clsfyprp.h"\
	{$(INCLUDE)}"\dstobwnd.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Ipropseq.hxx"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\propguid.h"\
	{$(INCLUDE)}"\Selidprp.h"\
	{$(INCLUDE)}"\selobwnd.h"\
	{$(INCLUDE)}"\selrlprp.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\use_ansi.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\fclassfy.obj" : $(SOURCE) $(DEP_CPP_FCLAS) "$(INTDIR)"\
 "$(INTDIR)\featured.pch"
   $(BuildCmds)

"$(INTDIR)\fclassfy.sbr" : $(SOURCE) $(DEP_CPP_FCLAS) "$(INTDIR)"\
 "$(INTDIR)\featured.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\FEATURE\enumonr.cxx

!IF  "$(CFG)" == "feature - Win32 Release"

DEP_CPP_ENUMO=\
	".\..\enumonr.hxx"\
	".\..\feature.hxx"\
	".\..\FEATUREP.HXX"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
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
	{$(INCLUDE)}"\Ipropseq.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ixtensnw.hxx"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\oprpguid.h"\
	{$(INCLUDE)}"\OSPACE\CONFIG.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\BC45.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\COMPILER.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HP3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HPGNU270.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\LOCAL.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\MS20.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\PLATFORM.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGIDCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGINCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN4.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS\Errors.h"\
	{$(INCLUDE)}"\OSPACE\THREADS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\AUTOLOCK.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\COUNTING.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\EVENT.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.CC"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MUTEX.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THISTHRD.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THREAD.H"\
	{$(INCLUDE)}"\OSPACE\TYPES.H"\
	{$(INCLUDE)}"\OSPACE\TYPES\Types.h"\
	{$(INCLUDE)}"\ostream"\
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
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\xtsnprop.hxx"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	

"$(INTDIR)\enumonr.obj" : $(SOURCE) $(DEP_CPP_ENUMO) "$(INTDIR)"\
 "$(INTDIR)\feature4.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "feature - Win32 Debug"

DEP_CPP_ENUMO=\
	".\..\enumonr.hxx"\
	".\..\FEATUREP.HXX"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\use_ansi.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\enumonr.obj" : $(SOURCE) $(DEP_CPP_ENUMO) "$(INTDIR)"\
 "$(INTDIR)\featured.pch"
   $(BuildCmds)

"$(INTDIR)\enumonr.sbr" : $(SOURCE) $(DEP_CPP_ENUMO) "$(INTDIR)"\
 "$(INTDIR)\featured.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\FEATURE\propactb.cxx

!IF  "$(CFG)" == "feature - Win32 Release"

DEP_CPP_PROPA=\
	".\..\enumonr.hxx"\
	".\..\feature.hxx"\
	".\..\FEATUREP.HXX"\
	".\..\propactb.hxx"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
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
	{$(INCLUDE)}"\Ipropseq.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ixtensnw.hxx"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\oprpguid.h"\
	{$(INCLUDE)}"\OSPACE\CONFIG.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\BC45.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\COMPILER.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HP3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HPGNU270.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\LOCAL.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\MS20.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\PLATFORM.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGIDCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGINCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN4.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS\Errors.h"\
	{$(INCLUDE)}"\OSPACE\THREADS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\AUTOLOCK.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\COUNTING.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\EVENT.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.CC"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MUTEX.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THISTHRD.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THREAD.H"\
	{$(INCLUDE)}"\OSPACE\TYPES.H"\
	{$(INCLUDE)}"\OSPACE\TYPES\Types.h"\
	{$(INCLUDE)}"\ostream"\
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
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\xtsnprop.hxx"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	

"$(INTDIR)\propactb.obj" : $(SOURCE) $(DEP_CPP_PROPA) "$(INTDIR)"\
 "$(INTDIR)\feature4.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "feature - Win32 Debug"

DEP_CPP_PROPA=\
	".\..\FEATUREP.HXX"\
	".\..\propactb.hxx"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\use_ansi.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\propactb.obj" : $(SOURCE) $(DEP_CPP_PROPA) "$(INTDIR)"\
 "$(INTDIR)\featured.pch"
   $(BuildCmds)

"$(INTDIR)\propactb.sbr" : $(SOURCE) $(DEP_CPP_PROPA) "$(INTDIR)"\
 "$(INTDIR)\featured.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\FEATURE\clspropb.cxx

!IF  "$(CFG)" == "feature - Win32 Release"

DEP_CPP_CLSPR=\
	".\..\clspropb.hxx"\
	".\..\enumonr.hxx"\
	".\..\feature.hxx"\
	".\..\FEATUREP.HXX"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
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
	{$(INCLUDE)}"\Ipropseq.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ixtensnw.hxx"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\oprpguid.h"\
	{$(INCLUDE)}"\OSPACE\CONFIG.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\BC45.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\COMPILER.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HP3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HPGNU270.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\LOCAL.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\MS20.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\PLATFORM.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGIDCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGINCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN4.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS\Errors.h"\
	{$(INCLUDE)}"\OSPACE\THREADS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\AUTOLOCK.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\COUNTING.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\EVENT.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.CC"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MUTEX.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THISTHRD.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THREAD.H"\
	{$(INCLUDE)}"\OSPACE\TYPES.H"\
	{$(INCLUDE)}"\OSPACE\TYPES\Types.h"\
	{$(INCLUDE)}"\ostream"\
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
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\xtsnprop.hxx"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	

"$(INTDIR)\clspropb.obj" : $(SOURCE) $(DEP_CPP_CLSPR) "$(INTDIR)"\
 "$(INTDIR)\feature4.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "feature - Win32 Debug"

DEP_CPP_CLSPR=\
	".\..\clspropb.hxx"\
	".\..\FEATUREP.HXX"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\use_ansi.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\clspropb.obj" : $(SOURCE) $(DEP_CPP_CLSPR) "$(INTDIR)"\
 "$(INTDIR)\featured.pch"
   $(BuildCmds)

"$(INTDIR)\clspropb.sbr" : $(SOURCE) $(DEP_CPP_CLSPR) "$(INTDIR)"\
 "$(INTDIR)\featured.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\FEATURE\datahelp.cxx

!IF  "$(CFG)" == "feature - Win32 Release"

DEP_CPP_DATAH=\
	".\..\enumonr.hxx"\
	".\..\feature.hxx"\
	".\..\FEATUREP.HXX"\
	".\..\strmhelp.hxx"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
	{$(INCLUDE)}"\clsfyprp.h"\
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
	{$(INCLUDE)}"\Ipropseq.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ixtensnw.hxx"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\oprpguid.h"\
	{$(INCLUDE)}"\OSPACE\CONFIG.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\BC45.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\COMPILER.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HP3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HPGNU270.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\LOCAL.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\MS20.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\PLATFORM.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGIDCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGINCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN4.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS\Errors.h"\
	{$(INCLUDE)}"\OSPACE\THREADS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\AUTOLOCK.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\COUNTING.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\EVENT.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.CC"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MUTEX.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THISTHRD.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THREAD.H"\
	{$(INCLUDE)}"\OSPACE\TYPES.H"\
	{$(INCLUDE)}"\OSPACE\TYPES\Types.h"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\propactn.h"\
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
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\xtsnprop.hxx"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	

"$(INTDIR)\datahelp.obj" : $(SOURCE) $(DEP_CPP_DATAH) "$(INTDIR)"\
 "$(INTDIR)\feature4.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "feature - Win32 Debug"

DEP_CPP_DATAH=\
	".\..\enumonr.hxx"\
	".\..\FEATUREP.HXX"\
	".\..\strmhelp.hxx"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\clsfyprp.h"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\oprpguid.h"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\use_ansi.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\datahelp.obj" : $(SOURCE) $(DEP_CPP_DATAH) "$(INTDIR)"\
 "$(INTDIR)\featured.pch"
   $(BuildCmds)

"$(INTDIR)\datahelp.sbr" : $(SOURCE) $(DEP_CPP_DATAH) "$(INTDIR)"\
 "$(INTDIR)\featured.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\FEATURE\selidlst.cxx

!IF  "$(CFG)" == "feature - Win32 Release"

DEP_CPP_SELID=\
	".\..\enumonr.hxx"\
	".\..\FEATURE.H"\
	".\..\feature.hxx"\
	".\..\FEATUREP.HXX"\
	".\..\SELIDLST.HXX"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
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
	{$(INCLUDE)}"\Ipropseq.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ixtensnw.hxx"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\oprpguid.h"\
	{$(INCLUDE)}"\OSPACE\CONFIG.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\BC45.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\COMPILER.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HP3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HPGNU270.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\LOCAL.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\MS20.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\PLATFORM.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGIDCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGINCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN4.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS\Errors.h"\
	{$(INCLUDE)}"\OSPACE\THREADS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\AUTOLOCK.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\COUNTING.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\EVENT.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.CC"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MUTEX.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THISTHRD.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THREAD.H"\
	{$(INCLUDE)}"\OSPACE\TYPES.H"\
	{$(INCLUDE)}"\OSPACE\TYPES\Types.h"\
	{$(INCLUDE)}"\ostream"\
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
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\xtsnprop.hxx"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	

"$(INTDIR)\selidlst.obj" : $(SOURCE) $(DEP_CPP_SELID) "$(INTDIR)"\
 "$(INTDIR)\feature4.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "feature - Win32 Debug"

DEP_CPP_SELID=\
	".\..\FEATURE.H"\
	".\..\FEATUREP.HXX"\
	".\..\SELIDLST.HXX"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\use_ansi.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\selidlst.obj" : $(SOURCE) $(DEP_CPP_SELID) "$(INTDIR)"\
 "$(INTDIR)\featured.pch"
   $(BuildCmds)

"$(INTDIR)\selidlst.sbr" : $(SOURCE) $(DEP_CPP_SELID) "$(INTDIR)"\
 "$(INTDIR)\featured.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\FEATURE\selident.cxx

!IF  "$(CFG)" == "feature - Win32 Release"

DEP_CPP_SELIDE=\
	".\..\enumonr.hxx"\
	".\..\FEATURE.H"\
	".\..\feature.hxx"\
	".\..\FEATUREP.HXX"\
	".\..\SELIDENT.HXX"\
	".\..\SELIDLST.HXX"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
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
	{$(INCLUDE)}"\Ipropseq.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ixtensnw.hxx"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\oprpguid.h"\
	{$(INCLUDE)}"\OSPACE\CONFIG.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\BC45.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\COMPILER.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HP3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HPGNU270.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\LOCAL.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\MS20.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\PLATFORM.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGIDCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGINCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN4.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS\Errors.h"\
	{$(INCLUDE)}"\OSPACE\THREADS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\AUTOLOCK.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\COUNTING.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\EVENT.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.CC"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MUTEX.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THISTHRD.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THREAD.H"\
	{$(INCLUDE)}"\OSPACE\TYPES.H"\
	{$(INCLUDE)}"\OSPACE\TYPES\Types.h"\
	{$(INCLUDE)}"\ostream"\
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
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\xtsnprop.hxx"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	

"$(INTDIR)\selident.obj" : $(SOURCE) $(DEP_CPP_SELIDE) "$(INTDIR)"\
 "$(INTDIR)\feature4.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "feature - Win32 Debug"

DEP_CPP_SELIDE=\
	".\..\enumonr.hxx"\
	".\..\FEATURE.H"\
	".\..\FEATUREP.HXX"\
	".\..\SELIDENT.HXX"\
	".\..\SELIDLST.HXX"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\use_ansi.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\selident.obj" : $(SOURCE) $(DEP_CPP_SELIDE) "$(INTDIR)"\
 "$(INTDIR)\featured.pch"
   $(BuildCmds)

"$(INTDIR)\selident.sbr" : $(SOURCE) $(DEP_CPP_SELIDE) "$(INTDIR)"\
 "$(INTDIR)\featured.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\FEATURE\selidprp.cxx

!IF  "$(CFG)" == "feature - Win32 Release"

DEP_CPP_SELIDP=\
	".\..\clspropb.hxx"\
	".\..\enumonr.hxx"\
	".\..\FEATURE.H"\
	".\..\feature.hxx"\
	".\..\FEATUREP.HXX"\
	".\..\propactb.hxx"\
	".\..\SELIDENT.HXX"\
	".\..\SELIDLST.HXX"\
	".\..\selidprp.hxx"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
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
	{$(INCLUDE)}"\Ipropseq.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ixtensnw.hxx"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\oprpguid.h"\
	{$(INCLUDE)}"\OSPACE\CONFIG.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\BC45.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\COMPILER.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HP3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HPGNU270.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\LOCAL.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\MS20.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\PLATFORM.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGIDCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGINCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN4.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS\Errors.h"\
	{$(INCLUDE)}"\OSPACE\THREADS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\AUTOLOCK.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\COUNTING.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\EVENT.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.CC"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MUTEX.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THISTHRD.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THREAD.H"\
	{$(INCLUDE)}"\OSPACE\TYPES.H"\
	{$(INCLUDE)}"\OSPACE\TYPES\Types.h"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\Pdataobj.hxx"\
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\propguid.h"\
	{$(INCLUDE)}"\Selidprp.h"\
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
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\xtsnprop.hxx"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	

"$(INTDIR)\selidprp.obj" : $(SOURCE) $(DEP_CPP_SELIDP) "$(INTDIR)"\
 "$(INTDIR)\feature4.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "feature - Win32 Debug"

DEP_CPP_SELIDP=\
	".\..\clspropb.hxx"\
	".\..\FEATURE.H"\
	".\..\FEATUREP.HXX"\
	".\..\propactb.hxx"\
	".\..\SELIDENT.HXX"\
	".\..\SELIDLST.HXX"\
	".\..\selidprp.hxx"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\Pdataobj.hxx"\
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\propguid.h"\
	{$(INCLUDE)}"\Selidprp.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\use_ansi.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\selidprp.obj" : $(SOURCE) $(DEP_CPP_SELIDP) "$(INTDIR)"\
 "$(INTDIR)\featured.pch"
   $(BuildCmds)

"$(INTDIR)\selidprp.sbr" : $(SOURCE) $(DEP_CPP_SELIDP) "$(INTDIR)"\
 "$(INTDIR)\featured.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\FEATURE\propname.cxx

!IF  "$(CFG)" == "feature - Win32 Release"

DEP_CPP_PROPN=\
	".\..\enumonr.hxx"\
	".\..\feature.hxx"\
	".\..\FEATUREP.HXX"\
	".\..\PROPNAME.HXX"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
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
	{$(INCLUDE)}"\Ipropseq.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ixtensnw.hxx"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\oprpguid.h"\
	{$(INCLUDE)}"\OSPACE\CONFIG.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\BC45.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\COMPILER.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HP3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HPGNU270.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\LOCAL.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\MS20.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\PLATFORM.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGIDCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGINCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN4.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS\Errors.h"\
	{$(INCLUDE)}"\OSPACE\THREADS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\AUTOLOCK.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\COUNTING.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\EVENT.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.CC"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MUTEX.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THISTHRD.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THREAD.H"\
	{$(INCLUDE)}"\OSPACE\TYPES.H"\
	{$(INCLUDE)}"\OSPACE\TYPES\Types.h"\
	{$(INCLUDE)}"\ostream"\
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
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\xtsnprop.hxx"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	

"$(INTDIR)\propname.obj" : $(SOURCE) $(DEP_CPP_PROPN) "$(INTDIR)"\
 "$(INTDIR)\feature4.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "feature - Win32 Debug"

DEP_CPP_PROPN=\
	".\..\FEATUREP.HXX"\
	".\..\PROPNAME.HXX"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\use_ansi.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\propname.obj" : $(SOURCE) $(DEP_CPP_PROPN) "$(INTDIR)"\
 "$(INTDIR)\featured.pch"
   $(BuildCmds)

"$(INTDIR)\propname.sbr" : $(SOURCE) $(DEP_CPP_PROPN) "$(INTDIR)"\
 "$(INTDIR)\featured.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\FEATURE\propseq.cxx

!IF  "$(CFG)" == "feature - Win32 Release"

DEP_CPP_PROPS=\
	".\..\enumonr.hxx"\
	".\..\FEATURE.H"\
	".\..\feature.hxx"\
	".\..\FEATUREP.HXX"\
	".\..\propseq.hxx"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
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
	{$(INCLUDE)}"\Ipropseq.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ixtensnw.hxx"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\oprpguid.h"\
	{$(INCLUDE)}"\OSPACE\CONFIG.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\BC45.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\COMPILER.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HP3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HPGNU270.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\LOCAL.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\MS20.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\PLATFORM.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGIDCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGINCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN4.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS\Errors.h"\
	{$(INCLUDE)}"\OSPACE\THREADS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\AUTOLOCK.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\COUNTING.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\EVENT.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.CC"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MUTEX.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THISTHRD.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THREAD.H"\
	{$(INCLUDE)}"\OSPACE\TYPES.H"\
	{$(INCLUDE)}"\OSPACE\TYPES\Types.h"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\propguid.h"\
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
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\xtsnprop.hxx"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	

"$(INTDIR)\propseq.obj" : $(SOURCE) $(DEP_CPP_PROPS) "$(INTDIR)"\
 "$(INTDIR)\feature4.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "feature - Win32 Debug"

DEP_CPP_PROPS=\
	".\..\FEATURE.H"\
	".\..\FEATUREP.HXX"\
	".\..\propseq.hxx"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Ipropseq.hxx"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\propguid.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\use_ansi.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\propseq.obj" : $(SOURCE) $(DEP_CPP_PROPS) "$(INTDIR)"\
 "$(INTDIR)\featured.pch"
   $(BuildCmds)

"$(INTDIR)\propseq.sbr" : $(SOURCE) $(DEP_CPP_PROPS) "$(INTDIR)"\
 "$(INTDIR)\featured.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\FEATURE\seloprop.cxx

!IF  "$(CFG)" == "feature - Win32 Release"

DEP_CPP_SELOP=\
	".\..\enumonr.hxx"\
	".\..\FEATURE.H"\
	".\..\feature.hxx"\
	".\..\FEATUREP.HXX"\
	".\..\seloprop.hxx"\
	".\..\seloprpt.hxx"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
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
	{$(INCLUDE)}"\Ipropseq.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ixtensnw.hxx"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\oprpguid.h"\
	{$(INCLUDE)}"\OSPACE\CONFIG.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\BC45.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\COMPILER.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HP3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HPGNU270.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\LOCAL.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\MS20.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\PLATFORM.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGIDCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGINCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN4.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS\Errors.h"\
	{$(INCLUDE)}"\OSPACE\THREADS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\AUTOLOCK.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\COUNTING.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\EVENT.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.CC"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MUTEX.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THISTHRD.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THREAD.H"\
	{$(INCLUDE)}"\OSPACE\TYPES.H"\
	{$(INCLUDE)}"\OSPACE\TYPES\Types.h"\
	{$(INCLUDE)}"\ostream"\
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
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\xtsnprop.hxx"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	

"$(INTDIR)\seloprop.obj" : $(SOURCE) $(DEP_CPP_SELOP) "$(INTDIR)"\
 "$(INTDIR)\feature4.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "__CV__" /D "MSWIND" /D "STRICT" /D\
 "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "NOMINMAX" /D\
 "OS_ALTERNATIVE_STRING_NAMES" /Fp"$(INTDIR)/feature4.pch" /Yu"featurep.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "feature - Win32 Debug"

# PROP Exclude_From_Build 0
DEP_CPP_SELOP=\
	".\..\enumonr.hxx"\
	".\..\FEATURE.H"\
	".\..\FEATUREP.HXX"\
	".\..\seloprop.hxx"\
	".\..\seloprpt.hxx"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\use_ansi.h"\
	
# ADD CPP /Zi

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "__CV__" /D "MSWIND"\
 /D "STRICT" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "NOMINMAX"\
 /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/featured.pch" /Yu"featurep.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/featured.pdb" /c $(SOURCE) \
	

"$(INTDIR)\seloprop.obj" : $(SOURCE) $(DEP_CPP_SELOP) "$(INTDIR)"\
 "$(INTDIR)\featured.pch"
   $(BuildCmds)

"$(INTDIR)\seloprop.sbr" : $(SOURCE) $(DEP_CPP_SELOP) "$(INTDIR)"\
 "$(INTDIR)\featured.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\FEATURE\seloprpt.cxx

!IF  "$(CFG)" == "feature - Win32 Release"

DEP_CPP_SELOPR=\
	".\..\enumonr.hxx"\
	".\..\feature.hxx"\
	".\..\FEATUREP.HXX"\
	".\..\PROPNAME.HXX"\
	".\..\seloprpt.hxx"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
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
	{$(INCLUDE)}"\Ipropseq.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ixtensnw.hxx"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\oprpguid.h"\
	{$(INCLUDE)}"\OSPACE\CONFIG.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\BC45.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\COMPILER.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HP3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HPGNU270.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\LOCAL.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\MS20.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\PLATFORM.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGIDCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGINCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN4.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS\Errors.h"\
	{$(INCLUDE)}"\OSPACE\THREADS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\AUTOLOCK.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\COUNTING.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\EVENT.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.CC"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MUTEX.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THISTHRD.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THREAD.H"\
	{$(INCLUDE)}"\OSPACE\TYPES.H"\
	{$(INCLUDE)}"\OSPACE\TYPES\Types.h"\
	{$(INCLUDE)}"\ostream"\
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
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\xtsnprop.hxx"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	

"$(INTDIR)\seloprpt.obj" : $(SOURCE) $(DEP_CPP_SELOPR) "$(INTDIR)"\
 "$(INTDIR)\feature4.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "__CV__" /D "MSWIND" /D "STRICT" /D\
 "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "NOMINMAX" /D\
 "OS_ALTERNATIVE_STRING_NAMES" /Fp"$(INTDIR)/feature4.pch" /Yu"featurep.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "feature - Win32 Debug"

DEP_CPP_SELOPR=\
	".\..\FEATUREP.HXX"\
	".\..\PROPNAME.HXX"\
	".\..\seloprpt.hxx"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\use_ansi.h"\
	
# ADD CPP /Zi

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "__CV__" /D "MSWIND"\
 /D "STRICT" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "NOMINMAX"\
 /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/featured.pch" /Yu"featurep.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/featured.pdb" /c $(SOURCE) \
	

"$(INTDIR)\seloprpt.obj" : $(SOURCE) $(DEP_CPP_SELOPR) "$(INTDIR)"\
 "$(INTDIR)\featured.pch"
   $(BuildCmds)

"$(INTDIR)\seloprpt.sbr" : $(SOURCE) $(DEP_CPP_SELOPR) "$(INTDIR)"\
 "$(INTDIR)\featured.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\FEATURE\clsfyprp.cxx

!IF  "$(CFG)" == "feature - Win32 Release"

DEP_CPP_CLSFY=\
	".\..\clsfyprp.hxx"\
	".\..\clspropb.hxx"\
	".\..\enumonr.hxx"\
	".\..\FEATURE.H"\
	".\..\feature.hxx"\
	".\..\FEATUREP.HXX"\
	".\..\propactb.hxx"\
	".\..\seloprop.hxx"\
	".\..\seloprpt.hxx"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
	{$(INCLUDE)}"\clsfyprp.h"\
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
	{$(INCLUDE)}"\Ipropseq.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ixtensnw.hxx"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\oprpguid.h"\
	{$(INCLUDE)}"\OSPACE\CONFIG.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\BC45.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\COMPILER.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HP3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HPGNU270.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\LOCAL.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\MS20.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\PLATFORM.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGIDCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGINCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN4.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS\Errors.h"\
	{$(INCLUDE)}"\OSPACE\THREADS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\AUTOLOCK.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\COUNTING.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\EVENT.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.CC"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MUTEX.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THISTHRD.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THREAD.H"\
	{$(INCLUDE)}"\OSPACE\TYPES.H"\
	{$(INCLUDE)}"\OSPACE\TYPES\Types.h"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\Pdataobj.hxx"\
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\propguid.h"\
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
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\xtsnprop.hxx"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	

"$(INTDIR)\clsfyprp.obj" : $(SOURCE) $(DEP_CPP_CLSFY) "$(INTDIR)"\
 "$(INTDIR)\feature4.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "__CV__" /D "MSWIND" /D "STRICT" /D\
 "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "NOMINMAX" /D\
 "OS_ALTERNATIVE_STRING_NAMES" /Fp"$(INTDIR)/feature4.pch" /Yu"featurep.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "feature - Win32 Debug"

DEP_CPP_CLSFY=\
	".\..\clsfyprp.hxx"\
	".\..\clspropb.hxx"\
	".\..\FEATURE.H"\
	".\..\FEATUREP.HXX"\
	".\..\propactb.hxx"\
	".\..\seloprop.hxx"\
	".\..\seloprpt.hxx"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\clsfyprp.h"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\Pdataobj.hxx"\
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\propguid.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\use_ansi.h"\
	
# ADD CPP /Zi

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "__CV__" /D "MSWIND"\
 /D "STRICT" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "NOMINMAX"\
 /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/featured.pch" /Yu"featurep.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/featured.pdb" /c $(SOURCE) \
	

"$(INTDIR)\clsfyprp.obj" : $(SOURCE) $(DEP_CPP_CLSFY) "$(INTDIR)"\
 "$(INTDIR)\featured.pch"
   $(BuildCmds)

"$(INTDIR)\clsfyprp.sbr" : $(SOURCE) $(DEP_CPP_CLSFY) "$(INTDIR)"\
 "$(INTDIR)\featured.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\FEATURE\selrelst.cxx

!IF  "$(CFG)" == "feature - Win32 Release"

DEP_CPP_SELRE=\
	".\..\enumonr.hxx"\
	".\..\FEATURE.H"\
	".\..\feature.hxx"\
	".\..\FEATUREP.HXX"\
	".\..\selrelst.hxx"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
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
	{$(INCLUDE)}"\Ipropseq.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ixtensnw.hxx"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\oprpguid.h"\
	{$(INCLUDE)}"\OSPACE\CONFIG.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\BC45.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\COMPILER.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HP3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HPGNU270.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\LOCAL.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\MS20.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\PLATFORM.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGIDCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGINCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN4.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS\Errors.h"\
	{$(INCLUDE)}"\OSPACE\THREADS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\AUTOLOCK.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\COUNTING.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\EVENT.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.CC"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MUTEX.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THISTHRD.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THREAD.H"\
	{$(INCLUDE)}"\OSPACE\TYPES.H"\
	{$(INCLUDE)}"\OSPACE\TYPES\Types.h"\
	{$(INCLUDE)}"\ostream"\
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
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\xtsnprop.hxx"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	

"$(INTDIR)\selrelst.obj" : $(SOURCE) $(DEP_CPP_SELRE) "$(INTDIR)"\
 "$(INTDIR)\feature4.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "feature - Win32 Debug"

DEP_CPP_SELRE=\
	".\..\FEATURE.H"\
	".\..\FEATUREP.HXX"\
	".\..\selrelst.hxx"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\use_ansi.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\selrelst.obj" : $(SOURCE) $(DEP_CPP_SELRE) "$(INTDIR)"\
 "$(INTDIR)\featured.pch"
   $(BuildCmds)

"$(INTDIR)\selrelst.sbr" : $(SOURCE) $(DEP_CPP_SELRE) "$(INTDIR)"\
 "$(INTDIR)\featured.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\FEATURE\selrcode.cxx

!IF  "$(CFG)" == "feature - Win32 Release"

DEP_CPP_SELRC=\
	".\..\enumonr.hxx"\
	".\..\FEATURE.H"\
	".\..\feature.hxx"\
	".\..\FEATUREP.HXX"\
	".\..\selidpbd.hxx"\
	".\..\selrcode.hxx"\
	".\..\selrelst.hxx"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
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
	{$(INCLUDE)}"\Ipropseq.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ixtensnw.hxx"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\oprpguid.h"\
	{$(INCLUDE)}"\OSPACE\CONFIG.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\BC45.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\COMPILER.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HP3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HPGNU270.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\LOCAL.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\MS20.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\PLATFORM.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGIDCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGINCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN4.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS\Errors.h"\
	{$(INCLUDE)}"\OSPACE\THREADS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\AUTOLOCK.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\COUNTING.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\EVENT.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.CC"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MUTEX.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THISTHRD.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THREAD.H"\
	{$(INCLUDE)}"\OSPACE\TYPES.H"\
	{$(INCLUDE)}"\OSPACE\TYPES\Types.h"\
	{$(INCLUDE)}"\ostream"\
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
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\xtsnprop.hxx"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	

"$(INTDIR)\selrcode.obj" : $(SOURCE) $(DEP_CPP_SELRC) "$(INTDIR)"\
 "$(INTDIR)\feature4.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "feature - Win32 Debug"

DEP_CPP_SELRC=\
	".\..\enumonr.hxx"\
	".\..\FEATURE.H"\
	".\..\FEATUREP.HXX"\
	".\..\selidpbd.hxx"\
	".\..\selrcode.hxx"\
	".\..\selrelst.hxx"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\use_ansi.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\selrcode.obj" : $(SOURCE) $(DEP_CPP_SELRC) "$(INTDIR)"\
 "$(INTDIR)\featured.pch"
   $(BuildCmds)

"$(INTDIR)\selrcode.sbr" : $(SOURCE) $(DEP_CPP_SELRC) "$(INTDIR)"\
 "$(INTDIR)\featured.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\FEATURE\selrlprp.cxx

!IF  "$(CFG)" == "feature - Win32 Release"

DEP_CPP_SELRL=\
	".\..\clspropb.hxx"\
	".\..\enumonr.hxx"\
	".\..\FEATURE.H"\
	".\..\feature.hxx"\
	".\..\FEATUREP.HXX"\
	".\..\propactb.hxx"\
	".\..\selrcode.hxx"\
	".\..\selrelst.hxx"\
	".\..\selrlprp.hxx"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
	{$(INCLUDE)}"\clsfyprp.h"\
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
	{$(INCLUDE)}"\Ipropseq.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ixtensnw.hxx"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\oprpguid.h"\
	{$(INCLUDE)}"\OSPACE\CONFIG.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\BC45.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\COMPILER.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HP3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HPGNU270.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\LOCAL.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\MS20.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\PLATFORM.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGIDCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGINCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN4.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS\Errors.h"\
	{$(INCLUDE)}"\OSPACE\THREADS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\AUTOLOCK.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\COUNTING.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\EVENT.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.CC"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MUTEX.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THISTHRD.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THREAD.H"\
	{$(INCLUDE)}"\OSPACE\TYPES.H"\
	{$(INCLUDE)}"\OSPACE\TYPES\Types.h"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\Pdataobj.hxx"\
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\propguid.h"\
	{$(INCLUDE)}"\selrlprp.h"\
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
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\xtsnprop.hxx"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	

"$(INTDIR)\selrlprp.obj" : $(SOURCE) $(DEP_CPP_SELRL) "$(INTDIR)"\
 "$(INTDIR)\feature4.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "feature - Win32 Debug"

DEP_CPP_SELRL=\
	".\..\clspropb.hxx"\
	".\..\FEATURE.H"\
	".\..\FEATUREP.HXX"\
	".\..\propactb.hxx"\
	".\..\selrcode.hxx"\
	".\..\selrelst.hxx"\
	".\..\selrlprp.hxx"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\clsfyprp.h"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\Pdataobj.hxx"\
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\propguid.h"\
	{$(INCLUDE)}"\selrlprp.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\use_ansi.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\selrlprp.obj" : $(SOURCE) $(DEP_CPP_SELRL) "$(INTDIR)"\
 "$(INTDIR)\featured.pch"
   $(BuildCmds)

"$(INTDIR)\selrlprp.sbr" : $(SOURCE) $(DEP_CPP_SELRL) "$(INTDIR)"\
 "$(INTDIR)\featured.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\FEATURE\selidpbd.cxx

!IF  "$(CFG)" == "feature - Win32 Release"

DEP_CPP_SELIDPB=\
	".\..\enumonr.hxx"\
	".\..\FEATURE.H"\
	".\..\feature.hxx"\
	".\..\FEATUREP.HXX"\
	".\..\selidpbd.hxx"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
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
	{$(INCLUDE)}"\Ipropseq.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ixtensnw.hxx"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\oprpguid.h"\
	{$(INCLUDE)}"\OSPACE\CONFIG.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\BC45.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\COMPILER.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HP3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HPGNU270.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\LOCAL.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\MS20.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\PLATFORM.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGIDCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGINCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN4.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS\Errors.h"\
	{$(INCLUDE)}"\OSPACE\THREADS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\AUTOLOCK.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\COUNTING.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\EVENT.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.CC"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MUTEX.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THISTHRD.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THREAD.H"\
	{$(INCLUDE)}"\OSPACE\TYPES.H"\
	{$(INCLUDE)}"\OSPACE\TYPES\Types.h"\
	{$(INCLUDE)}"\ostream"\
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
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\xtsnprop.hxx"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	

"$(INTDIR)\selidpbd.obj" : $(SOURCE) $(DEP_CPP_SELIDPB) "$(INTDIR)"\
 "$(INTDIR)\feature4.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "feature - Win32 Debug"

DEP_CPP_SELIDPB=\
	".\..\FEATURE.H"\
	".\..\FEATUREP.HXX"\
	".\..\selidpbd.hxx"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\use_ansi.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\selidpbd.obj" : $(SOURCE) $(DEP_CPP_SELIDPB) "$(INTDIR)"\
 "$(INTDIR)\featured.pch"
   $(BuildCmds)

"$(INTDIR)\selidpbd.sbr" : $(SOURCE) $(DEP_CPP_SELIDPB) "$(INTDIR)"\
 "$(INTDIR)\featured.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\FEATURE\DATAOBJ.CXX

!IF  "$(CFG)" == "feature - Win32 Release"

DEP_CPP_DATAO=\
	".\..\enumonr.hxx"\
	".\..\feature.hxx"\
	".\..\FEATUREP.HXX"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
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
	{$(INCLUDE)}"\Ipropseq.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ixtensnw.hxx"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\oprpguid.h"\
	{$(INCLUDE)}"\OSPACE\CONFIG.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\BC45.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\COMPILER.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HP3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HPGNU270.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\LOCAL.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\MS20.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\PLATFORM.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGIDCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGINCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN4.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS\Errors.h"\
	{$(INCLUDE)}"\OSPACE\THREADS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\AUTOLOCK.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\COUNTING.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\EVENT.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.CC"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MUTEX.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THISTHRD.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THREAD.H"\
	{$(INCLUDE)}"\OSPACE\TYPES.H"\
	{$(INCLUDE)}"\OSPACE\TYPES\Types.h"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\Pdataobj.hxx"\
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
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\xtsnprop.hxx"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	

"$(INTDIR)\DATAOBJ.OBJ" : $(SOURCE) $(DEP_CPP_DATAO) "$(INTDIR)"\
 "$(INTDIR)\feature4.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "feature - Win32 Debug"

DEP_CPP_DATAO=\
	".\..\FEATUREP.HXX"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\Pdataobj.hxx"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\use_ansi.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\DATAOBJ.OBJ" : $(SOURCE) $(DEP_CPP_DATAO) "$(INTDIR)"\
 "$(INTDIR)\featured.pch"
   $(BuildCmds)

"$(INTDIR)\DATAOBJ.SBR" : $(SOURCE) $(DEP_CPP_DATAO) "$(INTDIR)"\
 "$(INTDIR)\featured.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\FEATURE\IENUMFE.CXX

!IF  "$(CFG)" == "feature - Win32 Release"

DEP_CPP_IENUM=\
	".\..\enumonr.hxx"\
	".\..\feature.hxx"\
	".\..\FEATUREP.HXX"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
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
	{$(INCLUDE)}"\Ipropseq.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ixtensnw.hxx"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\oprpguid.h"\
	{$(INCLUDE)}"\OSPACE\CONFIG.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\BC45.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\COMPILER.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HP3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HPGNU270.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\LOCAL.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\MS20.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\PLATFORM.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGIDCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGINCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN4.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS\Errors.h"\
	{$(INCLUDE)}"\OSPACE\THREADS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\AUTOLOCK.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\COUNTING.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\EVENT.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.CC"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MUTEX.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THISTHRD.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THREAD.H"\
	{$(INCLUDE)}"\OSPACE\TYPES.H"\
	{$(INCLUDE)}"\OSPACE\TYPES\Types.h"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\Pdataobj.hxx"\
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
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\xtsnprop.hxx"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	

"$(INTDIR)\IENUMFE.OBJ" : $(SOURCE) $(DEP_CPP_IENUM) "$(INTDIR)"\
 "$(INTDIR)\feature4.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "feature - Win32 Debug"

DEP_CPP_IENUM=\
	".\..\FEATUREP.HXX"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\Pdataobj.hxx"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\use_ansi.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\IENUMFE.OBJ" : $(SOURCE) $(DEP_CPP_IENUM) "$(INTDIR)"\
 "$(INTDIR)\featured.pch"
   $(BuildCmds)

"$(INTDIR)\IENUMFE.SBR" : $(SOURCE) $(DEP_CPP_IENUM) "$(INTDIR)"\
 "$(INTDIR)\featured.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\FEATURE\IDATAOBJ.CXX

!IF  "$(CFG)" == "feature - Win32 Release"

DEP_CPP_IDATA=\
	".\..\enumonr.hxx"\
	".\..\feature.hxx"\
	".\..\FEATUREP.HXX"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
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
	{$(INCLUDE)}"\Ipropseq.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ixtensnw.hxx"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\oprpguid.h"\
	{$(INCLUDE)}"\OSPACE\CONFIG.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\BC45.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\COMPILER.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HP3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HPGNU270.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\LOCAL.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\MS20.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\PLATFORM.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGIDCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGINCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN4.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS\Errors.h"\
	{$(INCLUDE)}"\OSPACE\THREADS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\AUTOLOCK.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\COUNTING.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\EVENT.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.CC"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MUTEX.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THISTHRD.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THREAD.H"\
	{$(INCLUDE)}"\OSPACE\TYPES.H"\
	{$(INCLUDE)}"\OSPACE\TYPES\Types.h"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\Pdataobj.hxx"\
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
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\xtsnprop.hxx"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	

"$(INTDIR)\IDATAOBJ.OBJ" : $(SOURCE) $(DEP_CPP_IDATA) "$(INTDIR)"\
 "$(INTDIR)\feature4.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "feature - Win32 Debug"

DEP_CPP_IDATA=\
	".\..\FEATUREP.HXX"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\Pdataobj.hxx"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\use_ansi.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\IDATAOBJ.OBJ" : $(SOURCE) $(DEP_CPP_IDATA) "$(INTDIR)"\
 "$(INTDIR)\featured.pch"
   $(BuildCmds)

"$(INTDIR)\IDATAOBJ.SBR" : $(SOURCE) $(DEP_CPP_IDATA) "$(INTDIR)"\
 "$(INTDIR)\featured.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\FEATURE\selobwnd.cxx

!IF  "$(CFG)" == "feature - Win32 Release"

DEP_CPP_SELOB=\
	".\..\clspropb.hxx"\
	".\..\enumonr.hxx"\
	".\..\FEATURE.H"\
	".\..\feature.hxx"\
	".\..\FEATUREP.HXX"\
	".\..\propactb.hxx"\
	".\..\selobdlg.hxx"\
	".\..\selobwnd.hxx"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
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
	{$(INCLUDE)}"\Ipropseq.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ixtensnw.hxx"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\oprpguid.h"\
	{$(INCLUDE)}"\OSPACE\CONFIG.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\BC45.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\COMPILER.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HP3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HPGNU270.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\LOCAL.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\MS20.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\PLATFORM.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGIDCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGINCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN4.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS\Errors.h"\
	{$(INCLUDE)}"\OSPACE\THREADS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\AUTOLOCK.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\COUNTING.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\EVENT.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.CC"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MUTEX.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THISTHRD.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THREAD.H"\
	{$(INCLUDE)}"\OSPACE\TYPES.H"\
	{$(INCLUDE)}"\OSPACE\TYPES\Types.h"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\Pdataobj.hxx"\
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\propguid.h"\
	{$(INCLUDE)}"\selobwnd.h"\
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
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\xtsnprop.hxx"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	

"$(INTDIR)\selobwnd.obj" : $(SOURCE) $(DEP_CPP_SELOB) "$(INTDIR)"\
 "$(INTDIR)\feature4.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "feature - Win32 Debug"

DEP_CPP_SELOB=\
	".\..\clspropb.hxx"\
	".\..\FEATURE.H"\
	".\..\FEATUREP.HXX"\
	".\..\propactb.hxx"\
	".\..\selobdlg.hxx"\
	".\..\selobwnd.hxx"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\Pdataobj.hxx"\
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\propguid.h"\
	{$(INCLUDE)}"\selobwnd.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\use_ansi.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\selobwnd.obj" : $(SOURCE) $(DEP_CPP_SELOB) "$(INTDIR)"\
 "$(INTDIR)\featured.pch"
   $(BuildCmds)

"$(INTDIR)\selobwnd.sbr" : $(SOURCE) $(DEP_CPP_SELOB) "$(INTDIR)"\
 "$(INTDIR)\featured.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\FEATURE\selobdlg.cxx

!IF  "$(CFG)" == "feature - Win32 Release"

DEP_CPP_SELOBD=\
	".\..\enumonr.hxx"\
	".\..\FEATURE.H"\
	".\..\feature.hxx"\
	".\..\FEATUREP.HXX"\
	".\..\selobdlg.hxx"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
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
	{$(INCLUDE)}"\Ipropseq.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ixtensnw.hxx"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\oprpguid.h"\
	{$(INCLUDE)}"\OSPACE\CONFIG.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\BC45.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\COMPILER.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HP3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HPGNU270.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\LOCAL.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\MS20.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\PLATFORM.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGIDCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGINCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN4.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS\Errors.h"\
	{$(INCLUDE)}"\OSPACE\THREADS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\AUTOLOCK.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\COUNTING.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\EVENT.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.CC"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MUTEX.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THISTHRD.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THREAD.H"\
	{$(INCLUDE)}"\OSPACE\TYPES.H"\
	{$(INCLUDE)}"\OSPACE\TYPES\Types.h"\
	{$(INCLUDE)}"\ostream"\
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
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\xtsnprop.hxx"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	

"$(INTDIR)\selobdlg.obj" : $(SOURCE) $(DEP_CPP_SELOBD) "$(INTDIR)"\
 "$(INTDIR)\feature4.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "feature - Win32 Debug"

DEP_CPP_SELOBD=\
	".\..\enumonr.hxx"\
	".\..\FEATURE.H"\
	".\..\FEATUREP.HXX"\
	".\..\selobdlg.hxx"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\use_ansi.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\selobdlg.obj" : $(SOURCE) $(DEP_CPP_SELOBD) "$(INTDIR)"\
 "$(INTDIR)\featured.pch"
   $(BuildCmds)

"$(INTDIR)\selobdlg.sbr" : $(SOURCE) $(DEP_CPP_SELOBD) "$(INTDIR)"\
 "$(INTDIR)\featured.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\FEATURE\dstobwnd.cxx

!IF  "$(CFG)" == "feature - Win32 Release"

DEP_CPP_DSTOB=\
	".\..\clspropb.hxx"\
	".\..\dstobdlg.hxx"\
	".\..\dstobwnd.hxx"\
	".\..\enumonr.hxx"\
	".\..\FEATURE.H"\
	".\..\feature.hxx"\
	".\..\FEATUREP.HXX"\
	".\..\propactb.hxx"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
	{$(INCLUDE)}"\cstddef"\
	{$(INCLUDE)}"\cstdio"\
	{$(INCLUDE)}"\cstdlib"\
	{$(INCLUDE)}"\cstring"\
	{$(INCLUDE)}"\cwchar"\
	{$(INCLUDE)}"\dstobwnd.h"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\exception"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\ios"\
	{$(INCLUDE)}"\iosfwd"\
	{$(INCLUDE)}"\Ipropseq.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ixtensnw.hxx"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\oprpguid.h"\
	{$(INCLUDE)}"\OSPACE\CONFIG.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\BC45.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\COMPILER.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HP3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HPGNU270.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\LOCAL.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\MS20.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\PLATFORM.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGIDCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGINCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN4.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS\Errors.h"\
	{$(INCLUDE)}"\OSPACE\THREADS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\AUTOLOCK.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\COUNTING.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\EVENT.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.CC"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MUTEX.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THISTHRD.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THREAD.H"\
	{$(INCLUDE)}"\OSPACE\TYPES.H"\
	{$(INCLUDE)}"\OSPACE\TYPES\Types.h"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\Pdataobj.hxx"\
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\propguid.h"\
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
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\xtsnprop.hxx"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	

"$(INTDIR)\dstobwnd.obj" : $(SOURCE) $(DEP_CPP_DSTOB) "$(INTDIR)"\
 "$(INTDIR)\feature4.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "feature - Win32 Debug"

DEP_CPP_DSTOB=\
	".\..\clspropb.hxx"\
	".\..\dstobdlg.hxx"\
	".\..\dstobwnd.hxx"\
	".\..\FEATURE.H"\
	".\..\FEATUREP.HXX"\
	".\..\propactb.hxx"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\dstobwnd.h"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\Pdataobj.hxx"\
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\propguid.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\use_ansi.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\dstobwnd.obj" : $(SOURCE) $(DEP_CPP_DSTOB) "$(INTDIR)"\
 "$(INTDIR)\featured.pch"
   $(BuildCmds)

"$(INTDIR)\dstobwnd.sbr" : $(SOURCE) $(DEP_CPP_DSTOB) "$(INTDIR)"\
 "$(INTDIR)\featured.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\FEATURE\dstobdlg.cxx

!IF  "$(CFG)" == "feature - Win32 Release"

DEP_CPP_DSTOBD=\
	".\..\dstobdlg.hxx"\
	".\..\enumonr.hxx"\
	".\..\FEATURE.H"\
	".\..\feature.hxx"\
	".\..\FEATUREP.HXX"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
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
	{$(INCLUDE)}"\Ipropseq.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ixtensnw.hxx"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\oprpguid.h"\
	{$(INCLUDE)}"\OSPACE\CONFIG.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\BC45.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\COMPILER.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HP3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\HPGNU270.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\LOCAL.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\MS20.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\PLATFORM.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGIDCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SGINCC4.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN3.H"\
	{$(INCLUDE)}"\OSPACE\CONFIG\SUN4.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS.H"\
	{$(INCLUDE)}"\OSPACE\EVENTS\Errors.h"\
	{$(INCLUDE)}"\OSPACE\THREADS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\AUTOLOCK.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\COUNTING.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\EVENT.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.CC"\
	{$(INCLUDE)}"\OSPACE\THREADS\MONITORS.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\MUTEX.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THISTHRD.H"\
	{$(INCLUDE)}"\OSPACE\THREADS\THREAD.H"\
	{$(INCLUDE)}"\OSPACE\TYPES.H"\
	{$(INCLUDE)}"\OSPACE\TYPES\Types.h"\
	{$(INCLUDE)}"\ostream"\
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
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\xtsnprop.hxx"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	

"$(INTDIR)\dstobdlg.obj" : $(SOURCE) $(DEP_CPP_DSTOBD) "$(INTDIR)"\
 "$(INTDIR)\feature4.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "feature - Win32 Debug"

DEP_CPP_DSTOBD=\
	".\..\dstobdlg.hxx"\
	".\..\enumonr.hxx"\
	".\..\FEATURE.H"\
	".\..\FEATUREP.HXX"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\use_ansi.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\dstobdlg.obj" : $(SOURCE) $(DEP_CPP_DSTOBD) "$(INTDIR)"\
 "$(INTDIR)\featured.pch"
   $(BuildCmds)

"$(INTDIR)\dstobdlg.sbr" : $(SOURCE) $(DEP_CPP_DSTOBD) "$(INTDIR)"\
 "$(INTDIR)\featured.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\readme.txt

!IF  "$(CFG)" == "feature - Win32 Release"

!ELSEIF  "$(CFG)" == "feature - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
