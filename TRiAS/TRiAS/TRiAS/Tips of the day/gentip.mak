# Microsoft Developer Studio Generated NMAKE File, Format Version 40001
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

!IF "$(CFG)" == ""
CFG=gentip - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to gentip - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "gentip - Win32 Release" && "$(CFG)" != "gentip - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "gentip.mak" CFG="gentip - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "gentip - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "gentip - Win32 Debug" (based on "Win32 (x86) Console Application")
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
# PROP Target_Last_Scanned "gentip - Win32 Debug"
RSC=rc.exe
CPP=cl.exe

!IF  "$(CFG)" == "gentip - Win32 Release"

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

ALL : "$(OUTDIR)\gentip.exe"

CLEAN : 
	-@erase ".\Release\gentip.exe"
	-@erase ".\Release\gentip.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "OS_MULTI_THREADED" /D "NOMINMAX" /D "OS_ALTERNATIVE_STRING_NAMES" /YX /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D\
 "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "OS_MULTI_THREADED" /D\
 "NOMINMAX" /D "OS_ALTERNATIVE_STRING_NAMES" /Fp"$(INTDIR)/gentip.pch" /YX\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/gentip.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 ospacer.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
LINK32_FLAGS=ospacer.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)/gentip.pdb" /machine:I386 /out:"$(OUTDIR)/gentip.exe" 
LINK32_OBJS= \
	"$(INTDIR)/gentip.obj"

"$(OUTDIR)\gentip.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "gentip - Win32 Debug"

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

ALL : "$(OUTDIR)\gentip.exe"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\gentip.ilk"
	-@erase ".\Debug\gentip.obj"
	-@erase ".\Debug\gentip.pdb"
	-@erase ".\Debug\gentip.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "OS_MULTI_THREADED" /D "NOMINMAX" /D "OS_ALTERNATIVE_STRING_NAMES" /YX /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_CONSOLE"\
 /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "OS_MULTI_THREADED" /D\
 "NOMINMAX" /D "OS_ALTERNATIVE_STRING_NAMES" /Fp"$(INTDIR)/gentip.pch" /YX\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/gentip.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 ospaced.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
LINK32_FLAGS=ospaced.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)/gentip.pdb" /debug /machine:I386 /out:"$(OUTDIR)/gentip.exe" 
LINK32_OBJS= \
	"$(INTDIR)/gentip.obj"

"$(OUTDIR)\gentip.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "gentip - Win32 Release"
# Name "gentip - Win32 Debug"

!IF  "$(CFG)" == "gentip - Win32 Release"

!ELSEIF  "$(CFG)" == "gentip - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\gentip.cpp

!IF  "$(CFG)" == "gentip - Win32 Release"

DEP_CPP_GENTI=\
	{$(INCLUDE)}"\Ospace\String.h"\
	{$(INCLUDE)}"\Ospace\String\String.h"\
	{$(INCLUDE)}"\Ospace\String\Traits.h"\
	{$(INCLUDE)}"\Ospace\String\Basic.h"\
	{$(INCLUDE)}"\Ospace\String\Config.h"\
	{$(INCLUDE)}"\Ospace\Types.h"\
	{$(INCLUDE)}"\Ospace\String\Traits.cc"\
	{$(INCLUDE)}"\Ospace\Config.h"\
	{$(INCLUDE)}"\Ospace\Config\Compiler.h"\
	{$(INCLUDE)}"\Ospace\Config\Platform.h"\
	{$(INCLUDE)}"\Ospace\Config\Sun4.h"\
	{$(INCLUDE)}"\Ospace\Config\Sun3.h"\
	{$(INCLUDE)}"\Ospace\Config\Hp3.h"\
	{$(INCLUDE)}"\Ospace\Config\Ms20.h"\
	{$(INCLUDE)}"\Ospace\Config\Bc45.h"\
	{$(INCLUDE)}"\Ospace\Config\Dcc4.h"\
	{$(INCLUDE)}"\Ospace\Config\Local.h"\
	{$(INCLUDE)}"\Ospace\Types\Types.h"\
	{$(INCLUDE)}"\Ospace\String\Base.h"\
	{$(INCLUDE)}"\Ospace\Stl\Iterator.h"\
	{$(INCLUDE)}"\Ospace\String\Search.h"\
	{$(INCLUDE)}"\Ospace\Stl\Ops.h"\
	{$(INCLUDE)}"\Ospace\String\Basic.cc"\
	{$(INCLUDE)}"\Ospace\Stl\Common.h"\
	{$(INCLUDE)}"\Ospace\Stl\Allocate.h"\
	{$(INCLUDE)}"\Ospace\Events.h"\
	{$(INCLUDE)}"\Ospace\Stl\Config.h"\
	{$(INCLUDE)}"\Ospace\Stl\Rawaloc.h"\
	{$(INCLUDE)}"\Ospace\Stl\Lockaloc.h"\
	{$(INCLUDE)}"\Ospace\Events\Errors.h"\
	{$(INCLUDE)}"\Ospace\Threads.h"\
	{$(INCLUDE)}"\Ospace\Threads\Mutex.h"\
	{$(INCLUDE)}"\Ospace\Threads\Thisthrd.h"\
	{$(INCLUDE)}"\Ospace\Threads\Thread.h"\
	{$(INCLUDE)}"\Ospace\Threads\Autolock.h"\
	{$(INCLUDE)}"\Ospace\Threads\Monitors.h"\
	{$(INCLUDE)}"\Ospace\Threads\Counting.h"\
	{$(INCLUDE)}"\Ospace\Threads\Monitors.cc"\
	{$(INCLUDE)}"\Ospace\Threads\Event.h"\
	{$(INCLUDE)}"\Ospace\String\Search.cc"\
	

"$(INTDIR)\gentip.obj" : $(SOURCE) $(DEP_CPP_GENTI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "gentip - Win32 Debug"

DEP_CPP_GENTI=\
	{$(INCLUDE)}"\Ospace\String.h"\
	{$(INCLUDE)}"\Ospace\String\String.h"\
	{$(INCLUDE)}"\Ospace\String\Traits.h"\
	{$(INCLUDE)}"\Ospace\String\Config.h"\
	{$(INCLUDE)}"\Ospace\Config.h"\
	{$(INCLUDE)}"\Ospace\Config\Compiler.h"\
	

"$(INTDIR)\gentip.obj" : $(SOURCE) $(DEP_CPP_GENTI) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
