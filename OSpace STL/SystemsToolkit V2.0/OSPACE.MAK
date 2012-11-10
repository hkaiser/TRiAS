# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102
# TARGTYPE "Win32 (x86) Static Library" 0x0104

!IF "$(CFG)" == ""
CFG=standards uss - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to standards uss - Win32\
 Debug.
!ENDIF 

!IF "$(CFG)" != "standards - Win32 MT Debug" && "$(CFG)" !=\
 "standards - Win32 MT Release" && "$(CFG)" !=\
 "standards - Win32 MT Release Optimized" && "$(CFG)" !=\
 "standards uss - Win32 Release" && "$(CFG)" != "standards uss - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "OSPACE.MAK" CFG="standards uss - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "standards - Win32 MT Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "standards - Win32 MT Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "standards - Win32 MT Release Optimized" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "standards uss - Win32 Release" (based on\
 "Win32 (x86) Static Library")
!MESSAGE "standards uss - Win32 Debug" (based on "Win32 (x86) Static Library")
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
# PROP Target_Last_Scanned "standards - Win32 MT Release"

!IF  "$(CFG)" == "standards - Win32 MT Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "standard"
# PROP BASE Intermediate_Dir "standard"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
TargetName=ospaced
# End Custom Macros

ALL : "$(OUTDIR)\ospaced.dll" "..\..\..\trias.mvc\trias200\ospaced.dll"\
 "e:\triasdev.mvc\lib32\Ospace2d.lib" "e:\triasdev.mvc\lib32\Ospace2d.pdb"

CLEAN : 
	-@erase "$(INTDIR)\adapter.obj"
	-@erase "$(INTDIR)\ascii.obj"
	-@erase "$(INTDIR)\basic.obj"
	-@erase "$(INTDIR)\bstream.obj"
	-@erase "$(INTDIR)\bufdev.obj"
	-@erase "$(INTDIR)\buffer.obj"
	-@erase "$(INTDIR)\cache.obj"
	-@erase "$(INTDIR)\cast.obj"
	-@erase "$(INTDIR)\class.obj"
	-@erase "$(INTDIR)\classdb.obj"
	-@erase "$(INTDIR)\counting.obj"
	-@erase "$(INTDIR)\critical.obj"
	-@erase "$(INTDIR)\device.obj"
	-@erase "$(INTDIR)\dir.obj"
	-@erase "$(INTDIR)\eventsem.obj"
	-@erase "$(INTDIR)\file.obj"
	-@erase "$(INTDIR)\file_ex.obj"
	-@erase "$(INTDIR)\filedev.obj"
	-@erase "$(INTDIR)\fileinit.obj"
	-@erase "$(INTDIR)\filelock.obj"
	-@erase "$(INTDIR)\filesys.obj"
	-@erase "$(INTDIR)\fstrmdev.obj"
	-@erase "$(INTDIR)\helper_ex.obj"
	-@erase "$(INTDIR)\helpinit.obj"
	-@erase "$(INTDIR)\io_ex.obj"
	-@erase "$(INTDIR)\iocontrl.obj"
	-@erase "$(INTDIR)\ioinit.obj"
	-@erase "$(INTDIR)\IOLESTRM.OBJ"
	-@erase "$(INTDIR)\iostatus.obj"
	-@erase "$(INTDIR)\istrmdev.obj"
	-@erase "$(INTDIR)\mutex.obj"
	-@erase "$(INTDIR)\ndr.obj"
	-@erase "$(INTDIR)\OLEBUF.OBJ"
	-@erase "$(INTDIR)\OLEBUF1.OBJ"
	-@erase "$(INTDIR)\OLESTREA.OBJ"
	-@erase "$(INTDIR)\OOLESTRM.OBJ"
	-@erase "$(INTDIR)\openctrl.obj"
	-@erase "$(INTDIR)\ospace.obj"
	-@erase "$(INTDIR)\Ospace.res"
	-@erase "$(INTDIR)\ostrmdev.obj"
	-@erase "$(INTDIR)\path.obj"
	-@erase "$(INTDIR)\protocol.obj"
	-@erase "$(INTDIR)\randgen.obj"
	-@erase "$(INTDIR)\regex.obj"
	-@erase "$(INTDIR)\regexp.obj"
	-@erase "$(INTDIR)\rfifo.obj"
	-@erase "$(INTDIR)\rpriority.obj"
	-@erase "$(INTDIR)\rwsem.obj"
	-@erase "$(INTDIR)\sfifo.obj"
	-@erase "$(INTDIR)\sid.obj"
	-@erase "$(INTDIR)\smutex.obj"
	-@erase "$(INTDIR)\spriority.obj"
	-@erase "$(INTDIR)\strbuf.obj"
	-@erase "$(INTDIR)\stream_ex.obj"
	-@erase "$(INTDIR)\strhash.obj"
	-@erase "$(INTDIR)\string.obj"
	-@erase "$(INTDIR)\strmdev.obj"
	-@erase "$(INTDIR)\strminit.obj"
	-@erase "$(INTDIR)\thisthrd.obj"
	-@erase "$(INTDIR)\thread.obj"
	-@erase "$(INTDIR)\thread_ex.obj"
	-@erase "$(INTDIR)\tokenize.obj"
	-@erase "$(INTDIR)\treeaux.obj"
	-@erase "$(INTDIR)\tstream.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\vector.obj"
	-@erase "$(OUTDIR)\ospace2d.exp"
	-@erase "$(OUTDIR)\ospace2d.lib"
	-@erase "$(OUTDIR)\ospace2d.pdb"
	-@erase "$(OUTDIR)\ospaced.dll"
	-@erase "$(OUTDIR)\ospaced.ilk"
	-@erase "..\..\..\trias.mvc\trias200\ospaced.dll"
	-@erase "e:\triasdev.mvc\lib32\Ospace2d.lib"
	-@erase "e:\triasdev.mvc\lib32\Ospace2d.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /MD /W3 /Gm /GR /GX /Zi /Od /I "\toolkit" /I "\toolkit\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "OS_WIN_95" /D "OS_BUILD_DLL" /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /Zi /Od /D "_DEBUG" /D "OS_WIN_95" /D "OS_BUILD_DLL" /D "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS" /D "WIN32" /D "_WINDOWS" /D "OS_BUILD_IO_TOOLKIT" /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES" /YX /c
# SUBTRACT CPP /WX /Fr
CPP_PROJ=/nologo /MDd /W3 /Gm /GR /GX /Zi /Od /D "_DEBUG" /D "OS_WIN_95" /D\
 "OS_BUILD_DLL" /D "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS" /D "WIN32" /D\
 "_WINDOWS" /D "OS_BUILD_IO_TOOLKIT" /D "OS_NO_WSTRING" /D\
 "OS_ALTERNATIVE_STRING_NAMES" /Fp"$(INTDIR)/OSPACE.pch" /YX /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.

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

MTL=mktyplib.exe
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/Ospace.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/OSPACE.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"\toolkit\lib\std-2.0-vc4.0-mt-noalloc.dll"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /pdb:"Debug/ospace2d.pdb" /debug /machine:I386 /out:"Debug\ospaced.dll" /implib:"Debug/ospace2d.lib"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/ospace2d.pdb" /debug /machine:I386 /def:".\OSPACED.DEF"\
 /out:"$(OUTDIR)/ospaced.dll" /implib:"$(OUTDIR)/ospace2d.lib" 
DEF_FILE= \
	".\OSPACED.DEF"
LINK32_OBJS= \
	"$(INTDIR)\adapter.obj" \
	"$(INTDIR)\ascii.obj" \
	"$(INTDIR)\basic.obj" \
	"$(INTDIR)\bstream.obj" \
	"$(INTDIR)\bufdev.obj" \
	"$(INTDIR)\buffer.obj" \
	"$(INTDIR)\cache.obj" \
	"$(INTDIR)\cast.obj" \
	"$(INTDIR)\class.obj" \
	"$(INTDIR)\classdb.obj" \
	"$(INTDIR)\counting.obj" \
	"$(INTDIR)\critical.obj" \
	"$(INTDIR)\device.obj" \
	"$(INTDIR)\dir.obj" \
	"$(INTDIR)\eventsem.obj" \
	"$(INTDIR)\file.obj" \
	"$(INTDIR)\file_ex.obj" \
	"$(INTDIR)\filedev.obj" \
	"$(INTDIR)\fileinit.obj" \
	"$(INTDIR)\filelock.obj" \
	"$(INTDIR)\filesys.obj" \
	"$(INTDIR)\fstrmdev.obj" \
	"$(INTDIR)\helper_ex.obj" \
	"$(INTDIR)\helpinit.obj" \
	"$(INTDIR)\io_ex.obj" \
	"$(INTDIR)\iocontrl.obj" \
	"$(INTDIR)\ioinit.obj" \
	"$(INTDIR)\IOLESTRM.OBJ" \
	"$(INTDIR)\iostatus.obj" \
	"$(INTDIR)\istrmdev.obj" \
	"$(INTDIR)\mutex.obj" \
	"$(INTDIR)\ndr.obj" \
	"$(INTDIR)\OLEBUF.OBJ" \
	"$(INTDIR)\OLEBUF1.OBJ" \
	"$(INTDIR)\OLESTREA.OBJ" \
	"$(INTDIR)\OOLESTRM.OBJ" \
	"$(INTDIR)\openctrl.obj" \
	"$(INTDIR)\ospace.obj" \
	"$(INTDIR)\Ospace.res" \
	"$(INTDIR)\ostrmdev.obj" \
	"$(INTDIR)\path.obj" \
	"$(INTDIR)\protocol.obj" \
	"$(INTDIR)\randgen.obj" \
	"$(INTDIR)\regex.obj" \
	"$(INTDIR)\regexp.obj" \
	"$(INTDIR)\rfifo.obj" \
	"$(INTDIR)\rpriority.obj" \
	"$(INTDIR)\rwsem.obj" \
	"$(INTDIR)\sfifo.obj" \
	"$(INTDIR)\sid.obj" \
	"$(INTDIR)\smutex.obj" \
	"$(INTDIR)\spriority.obj" \
	"$(INTDIR)\strbuf.obj" \
	"$(INTDIR)\stream_ex.obj" \
	"$(INTDIR)\strhash.obj" \
	"$(INTDIR)\string.obj" \
	"$(INTDIR)\strmdev.obj" \
	"$(INTDIR)\strminit.obj" \
	"$(INTDIR)\thisthrd.obj" \
	"$(INTDIR)\thread.obj" \
	"$(INTDIR)\thread_ex.obj" \
	"$(INTDIR)\tokenize.obj" \
	"$(INTDIR)\treeaux.obj" \
	"$(INTDIR)\tstream.obj" \
	"$(INTDIR)\vector.obj"

"$(OUTDIR)\ospaced.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
TargetDir=.\Debug
TargetPath=.\Debug\ospaced.dll
TargetName=ospaced
InputPath=.\Debug\ospaced.dll
SOURCE=$(InputPath)

BuildCmds= \
	copy $(TargetPath) c:\trias.mvc\trias200 \
	copy $(TargetDir)\Ospace2d.lib e:\triasdev.mvc\lib32 \
	copy $(TargetDir)\Ospace2d.pdb e:\triasdev.mvc\lib32 \
	

"c:\trias.mvc\trias200\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"e:\triasdev.mvc\lib32\Ospace2d.lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"e:\triasdev.mvc\lib32\Ospace2d.pdb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "standar0"
# PROP BASE Intermediate_Dir "standar0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
TargetName=Ospacer
# End Custom Macros

ALL : "$(OUTDIR)\Ospacer.dll" "..\..\..\trias.mvc\trias200.rel\Ospacer.dll"\
 "e:\triasdev.mvc\lib32\Ospace2r.lib"

CLEAN : 
	-@erase "$(INTDIR)\adapter.obj"
	-@erase "$(INTDIR)\ascii.obj"
	-@erase "$(INTDIR)\basic.obj"
	-@erase "$(INTDIR)\bstream.obj"
	-@erase "$(INTDIR)\bufdev.obj"
	-@erase "$(INTDIR)\buffer.obj"
	-@erase "$(INTDIR)\cache.obj"
	-@erase "$(INTDIR)\cast.obj"
	-@erase "$(INTDIR)\class.obj"
	-@erase "$(INTDIR)\classdb.obj"
	-@erase "$(INTDIR)\counting.obj"
	-@erase "$(INTDIR)\critical.obj"
	-@erase "$(INTDIR)\device.obj"
	-@erase "$(INTDIR)\dir.obj"
	-@erase "$(INTDIR)\eventsem.obj"
	-@erase "$(INTDIR)\file.obj"
	-@erase "$(INTDIR)\file_ex.obj"
	-@erase "$(INTDIR)\filedev.obj"
	-@erase "$(INTDIR)\fileinit.obj"
	-@erase "$(INTDIR)\filelock.obj"
	-@erase "$(INTDIR)\filesys.obj"
	-@erase "$(INTDIR)\fstrmdev.obj"
	-@erase "$(INTDIR)\helper_ex.obj"
	-@erase "$(INTDIR)\helpinit.obj"
	-@erase "$(INTDIR)\io_ex.obj"
	-@erase "$(INTDIR)\iocontrl.obj"
	-@erase "$(INTDIR)\ioinit.obj"
	-@erase "$(INTDIR)\IOLESTRM.OBJ"
	-@erase "$(INTDIR)\iostatus.obj"
	-@erase "$(INTDIR)\istrmdev.obj"
	-@erase "$(INTDIR)\mutex.obj"
	-@erase "$(INTDIR)\ndr.obj"
	-@erase "$(INTDIR)\OLEBUF.OBJ"
	-@erase "$(INTDIR)\OLEBUF1.OBJ"
	-@erase "$(INTDIR)\OLESTREA.OBJ"
	-@erase "$(INTDIR)\OOLESTRM.OBJ"
	-@erase "$(INTDIR)\openctrl.obj"
	-@erase "$(INTDIR)\ospace.obj"
	-@erase "$(INTDIR)\Ospace.res"
	-@erase "$(INTDIR)\ostrmdev.obj"
	-@erase "$(INTDIR)\path.obj"
	-@erase "$(INTDIR)\protocol.obj"
	-@erase "$(INTDIR)\randgen.obj"
	-@erase "$(INTDIR)\regex.obj"
	-@erase "$(INTDIR)\regexp.obj"
	-@erase "$(INTDIR)\rfifo.obj"
	-@erase "$(INTDIR)\rpriority.obj"
	-@erase "$(INTDIR)\rwsem.obj"
	-@erase "$(INTDIR)\sfifo.obj"
	-@erase "$(INTDIR)\sid.obj"
	-@erase "$(INTDIR)\smutex.obj"
	-@erase "$(INTDIR)\spriority.obj"
	-@erase "$(INTDIR)\strbuf.obj"
	-@erase "$(INTDIR)\stream_ex.obj"
	-@erase "$(INTDIR)\strhash.obj"
	-@erase "$(INTDIR)\string.obj"
	-@erase "$(INTDIR)\strmdev.obj"
	-@erase "$(INTDIR)\strminit.obj"
	-@erase "$(INTDIR)\thisthrd.obj"
	-@erase "$(INTDIR)\thread.obj"
	-@erase "$(INTDIR)\thread_ex.obj"
	-@erase "$(INTDIR)\tokenize.obj"
	-@erase "$(INTDIR)\treeaux.obj"
	-@erase "$(INTDIR)\tstream.obj"
	-@erase "$(INTDIR)\vector.obj"
	-@erase "$(OUTDIR)\OSPACE2r.exp"
	-@erase "$(OUTDIR)\OSPACE2r.lib"
	-@erase "$(OUTDIR)\Ospacer.dll"
	-@erase "..\..\..\trias.mvc\trias200.rel\Ospacer.dll"
	-@erase "e:\triasdev.mvc\lib32\Ospace2r.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /MD /W3 /Gm /GR /GX /Zi /Od /I "\toolkit" /I "\toolkit\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "OS_WIN_95" /D "OS_BUILD_DLL" /YX /c
# ADD CPP /nologo /MD /W3 /GR /GX /Od /D "OS_WIN_95" /D "OS_BUILD_DLL" /D "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS" /D "WIN32" /D "_WINDOWS" /D "OS_BUILD_IO_TOOLKIT" /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES" /YX /c
# SUBTRACT CPP /WX
CPP_PROJ=/nologo /MD /W3 /GR /GX /Od /D "OS_WIN_95" /D "OS_BUILD_DLL" /D\
 "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS" /D "WIN32" /D "_WINDOWS" /D\
 "OS_BUILD_IO_TOOLKIT" /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES"\
 /Fp"$(INTDIR)/OSPACE.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.

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

MTL=mktyplib.exe
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/Ospace.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/OSPACE.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"\toolkit\lib\std-2.0-vc4.0-mt-noalloc.dll"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /machine:I386 /out:"Release/Ospacer.dll" /implib:"Release/OSPACE2r.lib"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/Ospacer.pdb" /machine:I386 /def:".\OSPACE.DEF"\
 /out:"$(OUTDIR)/Ospacer.dll" /implib:"$(OUTDIR)/OSPACE2r.lib" 
DEF_FILE= \
	".\OSPACE.DEF"
LINK32_OBJS= \
	"$(INTDIR)\adapter.obj" \
	"$(INTDIR)\ascii.obj" \
	"$(INTDIR)\basic.obj" \
	"$(INTDIR)\bstream.obj" \
	"$(INTDIR)\bufdev.obj" \
	"$(INTDIR)\buffer.obj" \
	"$(INTDIR)\cache.obj" \
	"$(INTDIR)\cast.obj" \
	"$(INTDIR)\class.obj" \
	"$(INTDIR)\classdb.obj" \
	"$(INTDIR)\counting.obj" \
	"$(INTDIR)\critical.obj" \
	"$(INTDIR)\device.obj" \
	"$(INTDIR)\dir.obj" \
	"$(INTDIR)\eventsem.obj" \
	"$(INTDIR)\file.obj" \
	"$(INTDIR)\file_ex.obj" \
	"$(INTDIR)\filedev.obj" \
	"$(INTDIR)\fileinit.obj" \
	"$(INTDIR)\filelock.obj" \
	"$(INTDIR)\filesys.obj" \
	"$(INTDIR)\fstrmdev.obj" \
	"$(INTDIR)\helper_ex.obj" \
	"$(INTDIR)\helpinit.obj" \
	"$(INTDIR)\io_ex.obj" \
	"$(INTDIR)\iocontrl.obj" \
	"$(INTDIR)\ioinit.obj" \
	"$(INTDIR)\IOLESTRM.OBJ" \
	"$(INTDIR)\iostatus.obj" \
	"$(INTDIR)\istrmdev.obj" \
	"$(INTDIR)\mutex.obj" \
	"$(INTDIR)\ndr.obj" \
	"$(INTDIR)\OLEBUF.OBJ" \
	"$(INTDIR)\OLEBUF1.OBJ" \
	"$(INTDIR)\OLESTREA.OBJ" \
	"$(INTDIR)\OOLESTRM.OBJ" \
	"$(INTDIR)\openctrl.obj" \
	"$(INTDIR)\ospace.obj" \
	"$(INTDIR)\Ospace.res" \
	"$(INTDIR)\ostrmdev.obj" \
	"$(INTDIR)\path.obj" \
	"$(INTDIR)\protocol.obj" \
	"$(INTDIR)\randgen.obj" \
	"$(INTDIR)\regex.obj" \
	"$(INTDIR)\regexp.obj" \
	"$(INTDIR)\rfifo.obj" \
	"$(INTDIR)\rpriority.obj" \
	"$(INTDIR)\rwsem.obj" \
	"$(INTDIR)\sfifo.obj" \
	"$(INTDIR)\sid.obj" \
	"$(INTDIR)\smutex.obj" \
	"$(INTDIR)\spriority.obj" \
	"$(INTDIR)\strbuf.obj" \
	"$(INTDIR)\stream_ex.obj" \
	"$(INTDIR)\strhash.obj" \
	"$(INTDIR)\string.obj" \
	"$(INTDIR)\strmdev.obj" \
	"$(INTDIR)\strminit.obj" \
	"$(INTDIR)\thisthrd.obj" \
	"$(INTDIR)\thread.obj" \
	"$(INTDIR)\thread_ex.obj" \
	"$(INTDIR)\tokenize.obj" \
	"$(INTDIR)\treeaux.obj" \
	"$(INTDIR)\tstream.obj" \
	"$(INTDIR)\vector.obj"

"$(OUTDIR)\Ospacer.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
TargetDir=.\Release
TargetPath=.\Release\Ospacer.dll
TargetName=Ospacer
InputPath=.\Release\Ospacer.dll
SOURCE=$(InputPath)

BuildCmds= \
	copy $(TargetPath) c:\trias.mvc\trias200.rel \
	copy $(TargetDir)\Ospace2r.lib e:\triasdev.mvc\lib32 \
	

"c:\trias.mvc\trias200.rel\$(TargetName).dll" : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
   $(BuildCmds)

"e:\triasdev.mvc\lib32\Ospace2r.lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "standard"
# PROP BASE Intermediate_Dir "standard"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "RelOpt"
# PROP Intermediate_Dir "RelOpt"
# PROP Target_Dir ""
OUTDIR=.\RelOpt
INTDIR=.\RelOpt
# Begin Custom Macros
TargetName=Ospacer
# End Custom Macros

ALL : "$(OUTDIR)\Ospacer.dll" "..\..\..\trias.mvc\trias200\Ospacer.dll"\
 "e:\triasdev.mvc\lib32\Ospace2r.lib"

CLEAN : 
	-@erase "$(INTDIR)\adapter.obj"
	-@erase "$(INTDIR)\ascii.obj"
	-@erase "$(INTDIR)\basic.obj"
	-@erase "$(INTDIR)\bstream.obj"
	-@erase "$(INTDIR)\bufdev.obj"
	-@erase "$(INTDIR)\buffer.obj"
	-@erase "$(INTDIR)\cache.obj"
	-@erase "$(INTDIR)\cast.obj"
	-@erase "$(INTDIR)\class.obj"
	-@erase "$(INTDIR)\classdb.obj"
	-@erase "$(INTDIR)\counting.obj"
	-@erase "$(INTDIR)\critical.obj"
	-@erase "$(INTDIR)\device.obj"
	-@erase "$(INTDIR)\dir.obj"
	-@erase "$(INTDIR)\eventsem.obj"
	-@erase "$(INTDIR)\file.obj"
	-@erase "$(INTDIR)\file_ex.obj"
	-@erase "$(INTDIR)\filedev.obj"
	-@erase "$(INTDIR)\fileinit.obj"
	-@erase "$(INTDIR)\filelock.obj"
	-@erase "$(INTDIR)\filesys.obj"
	-@erase "$(INTDIR)\fstrmdev.obj"
	-@erase "$(INTDIR)\helper_ex.obj"
	-@erase "$(INTDIR)\helpinit.obj"
	-@erase "$(INTDIR)\io_ex.obj"
	-@erase "$(INTDIR)\iocontrl.obj"
	-@erase "$(INTDIR)\ioinit.obj"
	-@erase "$(INTDIR)\IOLESTRM.OBJ"
	-@erase "$(INTDIR)\iostatus.obj"
	-@erase "$(INTDIR)\istrmdev.obj"
	-@erase "$(INTDIR)\mutex.obj"
	-@erase "$(INTDIR)\ndr.obj"
	-@erase "$(INTDIR)\OLEBUF.OBJ"
	-@erase "$(INTDIR)\OLEBUF1.OBJ"
	-@erase "$(INTDIR)\OLESTREA.OBJ"
	-@erase "$(INTDIR)\OOLESTRM.OBJ"
	-@erase "$(INTDIR)\openctrl.obj"
	-@erase "$(INTDIR)\ospace.obj"
	-@erase "$(INTDIR)\Ospace.res"
	-@erase "$(INTDIR)\ostrmdev.obj"
	-@erase "$(INTDIR)\path.obj"
	-@erase "$(INTDIR)\protocol.obj"
	-@erase "$(INTDIR)\randgen.obj"
	-@erase "$(INTDIR)\regex.obj"
	-@erase "$(INTDIR)\regexp.obj"
	-@erase "$(INTDIR)\rfifo.obj"
	-@erase "$(INTDIR)\rpriority.obj"
	-@erase "$(INTDIR)\rwsem.obj"
	-@erase "$(INTDIR)\sfifo.obj"
	-@erase "$(INTDIR)\sid.obj"
	-@erase "$(INTDIR)\smutex.obj"
	-@erase "$(INTDIR)\spriority.obj"
	-@erase "$(INTDIR)\strbuf.obj"
	-@erase "$(INTDIR)\stream_ex.obj"
	-@erase "$(INTDIR)\strhash.obj"
	-@erase "$(INTDIR)\string.obj"
	-@erase "$(INTDIR)\strmdev.obj"
	-@erase "$(INTDIR)\strminit.obj"
	-@erase "$(INTDIR)\thisthrd.obj"
	-@erase "$(INTDIR)\thread.obj"
	-@erase "$(INTDIR)\thread_ex.obj"
	-@erase "$(INTDIR)\tokenize.obj"
	-@erase "$(INTDIR)\treeaux.obj"
	-@erase "$(INTDIR)\tstream.obj"
	-@erase "$(INTDIR)\vector.obj"
	-@erase "$(OUTDIR)\Ospace2r.exp"
	-@erase "$(OUTDIR)\Ospace2r.lib"
	-@erase "$(OUTDIR)\Ospacer.dll"
	-@erase "..\..\..\trias.mvc\trias200\Ospacer.dll"
	-@erase "e:\triasdev.mvc\lib32\Ospace2r.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /MD /W3 /GR /GX /Od /I "\toolkit" /I "\toolit\ospace" /D "OS_WIN_95" /D "OS_BUILD_DLL" /D "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS" /D "WIN32" /D "_WINDOWS" /D "OS_BUILD_IO_TOOLKIT" /D "OS_NO_WSTRING" /YX /c
# SUBTRACT BASE CPP /WX
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /D "OS_WIN_95" /D "OS_BUILD_DLL" /D "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS" /D "WIN32" /D "_WINDOWS" /D "OS_BUILD_IO_TOOLKIT" /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES" /YX /c
# SUBTRACT CPP /WX
CPP_PROJ=/nologo /MD /W3 /GR /GX /O2 /D "OS_WIN_95" /D "OS_BUILD_DLL" /D\
 "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS" /D "WIN32" /D "_WINDOWS" /D\
 "OS_BUILD_IO_TOOLKIT" /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES"\
 /Fp"$(INTDIR)/OSPACE.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\RelOpt/
CPP_SBRS=.\.

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

MTL=mktyplib.exe
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
RSC=rc.exe
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/Ospace.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/OSPACE.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"RelOpt/Ospace2r.pdb" /machine:I386 /out:"RelOpt/Ospacer.dll" /implib:"RelOpt/Ospace2r.lib"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/Ospace2r.pdb" /machine:I386 /def:".\OSPACE.DEF"\
 /out:"$(OUTDIR)/Ospacer.dll" /implib:"$(OUTDIR)/Ospace2r.lib" 
DEF_FILE= \
	".\OSPACE.DEF"
LINK32_OBJS= \
	"$(INTDIR)\adapter.obj" \
	"$(INTDIR)\ascii.obj" \
	"$(INTDIR)\basic.obj" \
	"$(INTDIR)\bstream.obj" \
	"$(INTDIR)\bufdev.obj" \
	"$(INTDIR)\buffer.obj" \
	"$(INTDIR)\cache.obj" \
	"$(INTDIR)\cast.obj" \
	"$(INTDIR)\class.obj" \
	"$(INTDIR)\classdb.obj" \
	"$(INTDIR)\counting.obj" \
	"$(INTDIR)\critical.obj" \
	"$(INTDIR)\device.obj" \
	"$(INTDIR)\dir.obj" \
	"$(INTDIR)\eventsem.obj" \
	"$(INTDIR)\file.obj" \
	"$(INTDIR)\file_ex.obj" \
	"$(INTDIR)\filedev.obj" \
	"$(INTDIR)\fileinit.obj" \
	"$(INTDIR)\filelock.obj" \
	"$(INTDIR)\filesys.obj" \
	"$(INTDIR)\fstrmdev.obj" \
	"$(INTDIR)\helper_ex.obj" \
	"$(INTDIR)\helpinit.obj" \
	"$(INTDIR)\io_ex.obj" \
	"$(INTDIR)\iocontrl.obj" \
	"$(INTDIR)\ioinit.obj" \
	"$(INTDIR)\IOLESTRM.OBJ" \
	"$(INTDIR)\iostatus.obj" \
	"$(INTDIR)\istrmdev.obj" \
	"$(INTDIR)\mutex.obj" \
	"$(INTDIR)\ndr.obj" \
	"$(INTDIR)\OLEBUF.OBJ" \
	"$(INTDIR)\OLEBUF1.OBJ" \
	"$(INTDIR)\OLESTREA.OBJ" \
	"$(INTDIR)\OOLESTRM.OBJ" \
	"$(INTDIR)\openctrl.obj" \
	"$(INTDIR)\ospace.obj" \
	"$(INTDIR)\Ospace.res" \
	"$(INTDIR)\ostrmdev.obj" \
	"$(INTDIR)\path.obj" \
	"$(INTDIR)\protocol.obj" \
	"$(INTDIR)\randgen.obj" \
	"$(INTDIR)\regex.obj" \
	"$(INTDIR)\regexp.obj" \
	"$(INTDIR)\rfifo.obj" \
	"$(INTDIR)\rpriority.obj" \
	"$(INTDIR)\rwsem.obj" \
	"$(INTDIR)\sfifo.obj" \
	"$(INTDIR)\sid.obj" \
	"$(INTDIR)\smutex.obj" \
	"$(INTDIR)\spriority.obj" \
	"$(INTDIR)\strbuf.obj" \
	"$(INTDIR)\stream_ex.obj" \
	"$(INTDIR)\strhash.obj" \
	"$(INTDIR)\string.obj" \
	"$(INTDIR)\strmdev.obj" \
	"$(INTDIR)\strminit.obj" \
	"$(INTDIR)\thisthrd.obj" \
	"$(INTDIR)\thread.obj" \
	"$(INTDIR)\thread_ex.obj" \
	"$(INTDIR)\tokenize.obj" \
	"$(INTDIR)\treeaux.obj" \
	"$(INTDIR)\tstream.obj" \
	"$(INTDIR)\vector.obj"

"$(OUTDIR)\Ospacer.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
TargetDir=.\RelOpt
TargetPath=.\RelOpt\Ospacer.dll
TargetName=Ospacer
InputPath=.\RelOpt\Ospacer.dll
SOURCE=$(InputPath)

BuildCmds= \
	copy $(TargetPath) c:\trias.mvc\trias200 \
	copy $(TargetDir)\Ospace2r.lib e:\triasdev.mvc\lib32 \
	

"c:\trias.mvc\trias200\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"e:\triasdev.mvc\lib32\Ospace2r.lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "standards uss - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "standards uss\Release"
# PROP BASE Intermediate_Dir "standards uss\Release"
# PROP BASE Target_Dir "standards uss"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "RelUss"
# PROP Intermediate_Dir "RelUss"
# PROP Target_Dir "standards uss"
OUTDIR=.\RelUss
INTDIR=.\RelUss
# Begin Custom Macros
TargetName=StdStrmr
# End Custom Macros

ALL : "$(OUTDIR)\StdStrmr.lib" "e:\triasdev.mvc\lib32\StdStrmr.lib"

CLEAN : 
	-@erase "$(INTDIR)\file_uss.obj"
	-@erase "$(INTDIR)\std_uss.obj"
	-@erase "$(OUTDIR)\StdStrmr.lib"
	-@erase "e:\triasdev.mvc\lib32\StdStrmr.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /D "NDEBUG" /D "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS" /D "OS_WIN_95" /D "WIN32" /D "_WINDOWS" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES" /YX /c
CPP_PROJ=/nologo /MD /W3 /GR /GX /O2 /D "NDEBUG" /D "OS_MULTI_THREADED" /D\
 "OS_NO_ALLOCATORS" /D "OS_WIN_95" /D "WIN32" /D "_WINDOWS" /D "OS_STL_ASSERT"\
 /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES"\
 /Fp"$(INTDIR)/standards uss.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\RelUss/
CPP_SBRS=.\.

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

BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/standards uss.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"RelUss\StdStrmr.lib"
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/StdStrmr.lib" 
LIB32_OBJS= \
	"$(INTDIR)\file_uss.obj" \
	"$(INTDIR)\std_uss.obj"

"$(OUTDIR)\StdStrmr.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
TargetPath=.\RelUss\StdStrmr.lib
TargetName=StdStrmr
InputPath=.\RelUss\StdStrmr.lib
SOURCE=$(InputPath)

"e:\triasdev.mvc\lib32\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   copy $(TargetPath) e:\triasdev.mvc\lib32

# End Custom Build

!ELSEIF  "$(CFG)" == "standards uss - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "standards uss\Debug"
# PROP BASE Intermediate_Dir "standards uss\Debug"
# PROP BASE Target_Dir "standards uss"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugUss"
# PROP Intermediate_Dir "DebugUss"
# PROP Target_Dir "standards uss"
OUTDIR=.\DebugUss
INTDIR=.\DebugUss
# Begin Custom Macros
TargetName=StdStrmd
# End Custom Macros

ALL : "$(OUTDIR)\StdStrmd.lib" "e:\triasdev.mvc\lib32\StdStrmd.lib"

CLEAN : 
	-@erase "$(INTDIR)\file_uss.obj"
	-@erase "$(INTDIR)\std_uss.obj"
	-@erase "$(OUTDIR)\StdStrmd.lib"
	-@erase "e:\triasdev.mvc\lib32\StdStrmd.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /D "_DEBUG" /D "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS" /D "OS_WIN_95" /D "WIN32" /D "_WINDOWS" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES" /YX /c
CPP_PROJ=/nologo /MDd /W3 /GX /Z7 /Od /D "_DEBUG" /D "OS_MULTI_THREADED" /D\
 "OS_NO_ALLOCATORS" /D "OS_WIN_95" /D "WIN32" /D "_WINDOWS" /D "OS_STL_ASSERT"\
 /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES"\
 /Fp"$(INTDIR)/standards uss.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\DebugUss/
CPP_SBRS=.\.

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

BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/standards uss.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"DebugUss\StdStrmd.lib"
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/StdStrmd.lib" 
LIB32_OBJS= \
	"$(INTDIR)\file_uss.obj" \
	"$(INTDIR)\std_uss.obj"

"$(OUTDIR)\StdStrmd.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
TargetPath=.\DebugUss\StdStrmd.lib
TargetName=StdStrmd
InputPath=.\DebugUss\StdStrmd.lib
SOURCE=$(InputPath)

"e:\triasdev.mvc\lib32\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   copy $(TargetPath) e:\triasdev.mvc\lib32

# End Custom Build

!ENDIF 

################################################################################
# Begin Target

# Name "standards - Win32 MT Debug"
# Name "standards - Win32 MT Release"
# Name "standards - Win32 MT Release Optimized"

!IF  "$(CFG)" == "standards - Win32 MT Debug"

!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"

!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=\toolkit\ospace\stl\src\vector.cpp
DEP_CPP_VECTO=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\except\config.h"\
	{$(INCLUDE)}"\..\except\except.h"\
	{$(INCLUDE)}"\..\except\stdex.h"\
	{$(INCLUDE)}"\..\internal\fmacros.h"\
	{$(INCLUDE)}"\..\std\iosfwd"\
	{$(INCLUDE)}"\..\std\istream"\
	{$(INCLUDE)}"\..\std\ostream"\
	{$(INCLUDE)}"\..\stl\allocate.cc"\
	{$(INCLUDE)}"\..\stl\allocate.h"\
	{$(INCLUDE)}"\..\stl\allocimp.h"\
	{$(INCLUDE)}"\..\stl\basalgo.cc"\
	{$(INCLUDE)}"\..\stl\basalgo.h"\
	{$(INCLUDE)}"\..\stl\common.h"\
	{$(INCLUDE)}"\..\stl\config.h"\
	{$(INCLUDE)}"\..\stl\iterator.cc"\
	{$(INCLUDE)}"\..\stl\iterator.h"\
	{$(INCLUDE)}"\..\stl\ops.h"\
	{$(INCLUDE)}"\..\stl\pair.h"\
	{$(INCLUDE)}"\..\stl\rawalgo.cc"\
	{$(INCLUDE)}"\..\stl\rawalgo.h"\
	{$(INCLUDE)}"\..\stl\stlerror.h"\
	{$(INCLUDE)}"\..\stl\vector.cc"\
	{$(INCLUDE)}"\..\stl\vector.h"\
	{$(INCLUDE)}"\..\string\basic.cc"\
	{$(INCLUDE)}"\..\string\basic.h"\
	{$(INCLUDE)}"\..\string\basic.ipp"\
	{$(INCLUDE)}"\..\string\config.h"\
	{$(INCLUDE)}"\..\string\search.cc"\
	{$(INCLUDE)}"\..\string\search.h"\
	{$(INCLUDE)}"\..\string\string.h"\
	{$(INCLUDE)}"\..\string\traits.cc"\
	{$(INCLUDE)}"\..\string\traits.h"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\..\utility\memory.h"\
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
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
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
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\vector.obj" : $(SOURCE) $(DEP_CPP_VECTO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\vector.obj" : $(SOURCE) $(DEP_CPP_VECTO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\vector.obj" : $(SOURCE) $(DEP_CPP_VECTO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\toolkit\ospace\stl\src\treeaux.cpp
DEP_CPP_TREEA=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\internal\fmacros.h"\
	{$(INCLUDE)}"\..\stl\allocate.cc"\
	{$(INCLUDE)}"\..\stl\allocate.h"\
	{$(INCLUDE)}"\..\stl\allocimp.h"\
	{$(INCLUDE)}"\..\stl\common.h"\
	{$(INCLUDE)}"\..\stl\config.h"\
	{$(INCLUDE)}"\..\stl\stlerror.h"\
	{$(INCLUDE)}"\..\stl\treeaux.h"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\treeaux.obj" : $(SOURCE) $(DEP_CPP_TREEA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\treeaux.obj" : $(SOURCE) $(DEP_CPP_TREEA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\treeaux.obj" : $(SOURCE) $(DEP_CPP_TREEA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\toolkit\ospace\stl\src\randgen.cpp
DEP_CPP_RANDG=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\stl\randgen.h"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\randgen.obj" : $(SOURCE) $(DEP_CPP_RANDG) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\randgen.obj" : $(SOURCE) $(DEP_CPP_RANDG) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\randgen.obj" : $(SOURCE) $(DEP_CPP_RANDG) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\toolkit\ospace\string\src\basic.cpp
DEP_CPP_BASIC=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\except\config.h"\
	{$(INCLUDE)}"\..\except\except.h"\
	{$(INCLUDE)}"\..\except\stdex.h"\
	{$(INCLUDE)}"\..\internal\fmacros.h"\
	{$(INCLUDE)}"\..\std\iosfwd"\
	{$(INCLUDE)}"\..\std\istream"\
	{$(INCLUDE)}"\..\std\ostream"\
	{$(INCLUDE)}"\..\std\stdexcept"\
	{$(INCLUDE)}"\..\stl\allocate.cc"\
	{$(INCLUDE)}"\..\stl\allocate.h"\
	{$(INCLUDE)}"\..\stl\allocimp.h"\
	{$(INCLUDE)}"\..\stl\common.h"\
	{$(INCLUDE)}"\..\stl\config.h"\
	{$(INCLUDE)}"\..\stl\iterator.cc"\
	{$(INCLUDE)}"\..\stl\iterator.h"\
	{$(INCLUDE)}"\..\stl\ops.h"\
	{$(INCLUDE)}"\..\stl\pair.h"\
	{$(INCLUDE)}"\..\stl\stlerror.h"\
	{$(INCLUDE)}"\..\string\basic.cc"\
	{$(INCLUDE)}"\..\string\basic.h"\
	{$(INCLUDE)}"\..\string\basic.ipp"\
	{$(INCLUDE)}"\..\string\config.h"\
	{$(INCLUDE)}"\..\string\search.cc"\
	{$(INCLUDE)}"\..\string\search.h"\
	{$(INCLUDE)}"\..\string\string.h"\
	{$(INCLUDE)}"\..\string\traits.cc"\
	{$(INCLUDE)}"\..\string\traits.h"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\..\utility\memory.h"\
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
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
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
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\basic.obj" : $(SOURCE) $(DEP_CPP_BASIC) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\basic.obj" : $(SOURCE) $(DEP_CPP_BASIC) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\basic.obj" : $(SOURCE) $(DEP_CPP_BASIC) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\toolkit\ospace\string\src\string.cpp
DEP_CPP_STRIN=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\internal\fmacros.h"\
	{$(INCLUDE)}"\..\std\iosfwd"\
	{$(INCLUDE)}"\..\std\istream"\
	{$(INCLUDE)}"\..\std\ostream"\
	{$(INCLUDE)}"\..\stl\allocate.cc"\
	{$(INCLUDE)}"\..\stl\allocate.h"\
	{$(INCLUDE)}"\..\stl\allocimp.h"\
	{$(INCLUDE)}"\..\stl\common.h"\
	{$(INCLUDE)}"\..\stl\config.h"\
	{$(INCLUDE)}"\..\stl\iterator.cc"\
	{$(INCLUDE)}"\..\stl\iterator.h"\
	{$(INCLUDE)}"\..\stl\ops.h"\
	{$(INCLUDE)}"\..\stl\pair.h"\
	{$(INCLUDE)}"\..\stl\stlerror.h"\
	{$(INCLUDE)}"\..\string\basic.cc"\
	{$(INCLUDE)}"\..\string\basic.h"\
	{$(INCLUDE)}"\..\string\basic.ipp"\
	{$(INCLUDE)}"\..\string\config.h"\
	{$(INCLUDE)}"\..\string\search.cc"\
	{$(INCLUDE)}"\..\string\search.h"\
	{$(INCLUDE)}"\..\string\string.h"\
	{$(INCLUDE)}"\..\string\traits.cc"\
	{$(INCLUDE)}"\..\string\traits.h"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\..\utility\memory.h"\
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
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
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
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\string.obj" : $(SOURCE) $(DEP_CPP_STRIN) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\string.obj" : $(SOURCE) $(DEP_CPP_STRIN) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\string.obj" : $(SOURCE) $(DEP_CPP_STRIN) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\toolkit\ospace\string\src\strhash.cpp
DEP_CPP_STRHA=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\internal\fmacros.h"\
	{$(INCLUDE)}"\..\std\iosfwd"\
	{$(INCLUDE)}"\..\std\istream"\
	{$(INCLUDE)}"\..\std\ostream"\
	{$(INCLUDE)}"\..\std\string"\
	{$(INCLUDE)}"\..\stl\allocate.cc"\
	{$(INCLUDE)}"\..\stl\allocate.h"\
	{$(INCLUDE)}"\..\stl\allocimp.h"\
	{$(INCLUDE)}"\..\stl\common.h"\
	{$(INCLUDE)}"\..\stl\config.h"\
	{$(INCLUDE)}"\..\stl\iterator.cc"\
	{$(INCLUDE)}"\..\stl\iterator.h"\
	{$(INCLUDE)}"\..\stl\ops.h"\
	{$(INCLUDE)}"\..\stl\pair.h"\
	{$(INCLUDE)}"\..\stl\stlerror.h"\
	{$(INCLUDE)}"\..\string\basic.cc"\
	{$(INCLUDE)}"\..\string\basic.h"\
	{$(INCLUDE)}"\..\string\basic.ipp"\
	{$(INCLUDE)}"\..\string\config.h"\
	{$(INCLUDE)}"\..\string\search.cc"\
	{$(INCLUDE)}"\..\string\search.h"\
	{$(INCLUDE)}"\..\string\strhash.h"\
	{$(INCLUDE)}"\..\string\string.h"\
	{$(INCLUDE)}"\..\string\traits.cc"\
	{$(INCLUDE)}"\..\string\traits.h"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\..\utility\memory.h"\
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
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
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
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\strhash.obj" : $(SOURCE) $(DEP_CPP_STRHA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\strhash.obj" : $(SOURCE) $(DEP_CPP_STRHA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\strhash.obj" : $(SOURCE) $(DEP_CPP_STRHA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\except\src\helper_ex.cpp
DEP_CPP_HELPE=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\except\helper.h"\
	{$(INCLUDE)}"\..\except\helper.ipp"\
	{$(INCLUDE)}"\..\except\toolkit.h"\
	{$(INCLUDE)}"\..\except\toolkit.ipp"\
	{$(INCLUDE)}"\..\std\iostream"\
	{$(INCLUDE)}"\..\type\prim.h"\
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
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
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
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\helper_ex.obj" : $(SOURCE) $(DEP_CPP_HELPE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\helper_ex.obj" : $(SOURCE) $(DEP_CPP_HELPE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\helper_ex.obj" : $(SOURCE) $(DEP_CPP_HELPE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\string\src\tokenize.cpp
DEP_CPP_TOKEN=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\except\config.h"\
	{$(INCLUDE)}"\..\except\except.h"\
	{$(INCLUDE)}"\..\except\stdex.h"\
	{$(INCLUDE)}"\..\internal\fmacros.h"\
	{$(INCLUDE)}"\..\std\iosfwd"\
	{$(INCLUDE)}"\..\std\istream"\
	{$(INCLUDE)}"\..\std\ostream"\
	{$(INCLUDE)}"\..\std\string"\
	{$(INCLUDE)}"\..\std\vector"\
	{$(INCLUDE)}"\..\stl\allocate.cc"\
	{$(INCLUDE)}"\..\stl\allocate.h"\
	{$(INCLUDE)}"\..\stl\allocimp.h"\
	{$(INCLUDE)}"\..\stl\basalgo.cc"\
	{$(INCLUDE)}"\..\stl\basalgo.h"\
	{$(INCLUDE)}"\..\stl\common.h"\
	{$(INCLUDE)}"\..\stl\config.h"\
	{$(INCLUDE)}"\..\stl\iterator.cc"\
	{$(INCLUDE)}"\..\stl\iterator.h"\
	{$(INCLUDE)}"\..\stl\ops.h"\
	{$(INCLUDE)}"\..\stl\pair.h"\
	{$(INCLUDE)}"\..\stl\rawalgo.cc"\
	{$(INCLUDE)}"\..\stl\rawalgo.h"\
	{$(INCLUDE)}"\..\stl\stlerror.h"\
	{$(INCLUDE)}"\..\stl\vector.cc"\
	{$(INCLUDE)}"\..\stl\vector.h"\
	{$(INCLUDE)}"\..\string\basic.cc"\
	{$(INCLUDE)}"\..\string\basic.h"\
	{$(INCLUDE)}"\..\string\basic.ipp"\
	{$(INCLUDE)}"\..\string\config.h"\
	{$(INCLUDE)}"\..\string\search.cc"\
	{$(INCLUDE)}"\..\string\search.h"\
	{$(INCLUDE)}"\..\string\string.h"\
	{$(INCLUDE)}"\..\string\tokenize.h"\
	{$(INCLUDE)}"\..\string\tokenize.ipp"\
	{$(INCLUDE)}"\..\string\traits.cc"\
	{$(INCLUDE)}"\..\string\traits.h"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\..\utility\memory.h"\
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
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
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
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\tokenize.obj" : $(SOURCE) $(DEP_CPP_TOKEN) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\tokenize.obj" : $(SOURCE) $(DEP_CPP_TOKEN) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\tokenize.obj" : $(SOURCE) $(DEP_CPP_TOKEN) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\string\src\regex.cpp
DEP_CPP_REGEX=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\string\src\regex.h"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	
NODEP_CPP_REGEX=\
	"..\string\src\buffer.h"\
	"..\string\src\lisp.h"\
	"..\string\src\syntax.h"\
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\regex.obj" : $(SOURCE) $(DEP_CPP_REGEX) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\regex.obj" : $(SOURCE) $(DEP_CPP_REGEX) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\regex.obj" : $(SOURCE) $(DEP_CPP_REGEX) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\string\src\regexp.cpp
DEP_CPP_REGEXP=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\except\config.h"\
	{$(INCLUDE)}"\..\except\except.h"\
	{$(INCLUDE)}"\..\except\helper.h"\
	{$(INCLUDE)}"\..\except\helper.ipp"\
	{$(INCLUDE)}"\..\except\stdex.h"\
	{$(INCLUDE)}"\..\except\toolkit.h"\
	{$(INCLUDE)}"\..\except\toolkit.ipp"\
	{$(INCLUDE)}"\..\internal\fmacros.h"\
	{$(INCLUDE)}"\..\std\iosfwd"\
	{$(INCLUDE)}"\..\std\iostream"\
	{$(INCLUDE)}"\..\std\istream"\
	{$(INCLUDE)}"\..\std\ostream"\
	{$(INCLUDE)}"\..\std\stdexcept"\
	{$(INCLUDE)}"\..\std\string"\
	{$(INCLUDE)}"\..\stl\allocate.cc"\
	{$(INCLUDE)}"\..\stl\allocate.h"\
	{$(INCLUDE)}"\..\stl\allocimp.h"\
	{$(INCLUDE)}"\..\stl\common.h"\
	{$(INCLUDE)}"\..\stl\config.h"\
	{$(INCLUDE)}"\..\stl\iterator.cc"\
	{$(INCLUDE)}"\..\stl\iterator.h"\
	{$(INCLUDE)}"\..\stl\ops.h"\
	{$(INCLUDE)}"\..\stl\pair.h"\
	{$(INCLUDE)}"\..\stl\stlerror.h"\
	{$(INCLUDE)}"\..\string\basic.cc"\
	{$(INCLUDE)}"\..\string\basic.h"\
	{$(INCLUDE)}"\..\string\basic.ipp"\
	{$(INCLUDE)}"\..\string\config.h"\
	{$(INCLUDE)}"\..\string\regexp.h"\
	{$(INCLUDE)}"\..\string\regexp.ipp"\
	{$(INCLUDE)}"\..\string\search.cc"\
	{$(INCLUDE)}"\..\string\search.h"\
	{$(INCLUDE)}"\..\string\src\regex.h"\
	{$(INCLUDE)}"\..\string\string.h"\
	{$(INCLUDE)}"\..\string\substr.cc"\
	{$(INCLUDE)}"\..\string\substr.h"\
	{$(INCLUDE)}"\..\string\substr.ipp"\
	{$(INCLUDE)}"\..\string\traits.cc"\
	{$(INCLUDE)}"\..\string\traits.h"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\..\utility\memory.h"\
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
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
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
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\regexp.obj" : $(SOURCE) $(DEP_CPP_REGEXP) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\regexp.obj" : $(SOURCE) $(DEP_CPP_REGEXP) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\regexp.obj" : $(SOURCE) $(DEP_CPP_REGEXP) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\string\src\helpinit.cpp
DEP_CPP_HELPI=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\string\_startup.h"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\helpinit.obj" : $(SOURCE) $(DEP_CPP_HELPI) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\helpinit.obj" : $(SOURCE) $(DEP_CPP_HELPI) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\helpinit.obj" : $(SOURCE) $(DEP_CPP_HELPI) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\dll\src\ospace.cpp
DEP_CPP_OSPAC=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\std\iostream"\
	{$(INCLUDE)}"\..\string\src\regex.h"\
	{$(INCLUDE)}"\..\type\prim.h"\
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
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
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
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\ospace.obj" : $(SOURCE) $(DEP_CPP_OSPAC) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\ospace.obj" : $(SOURCE) $(DEP_CPP_OSPAC) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\ospace.obj" : $(SOURCE) $(DEP_CPP_OSPAC) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Ospace.rc

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\Ospace.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\Ospace.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\Ospace.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\io\src\sid.cpp
DEP_CPP_SID_C=\
	"..\utility\autoptr.org.h"\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\except\io.h"\
	{$(INCLUDE)}"\..\except\io.ipp"\
	{$(INCLUDE)}"\..\except\throw.h"\
	{$(INCLUDE)}"\..\except\toolkit.h"\
	{$(INCLUDE)}"\..\except\toolkit.ipp"\
	{$(INCLUDE)}"\..\internal\call.h"\
	{$(INCLUDE)}"\..\internal\errno.h"\
	{$(INCLUDE)}"\..\internal\error.h"\
	{$(INCLUDE)}"\..\internal\syscall.h"\
	{$(INCLUDE)}"\..\io\sid.h"\
	{$(INCLUDE)}"\..\std\iostream"\
	{$(INCLUDE)}"\..\std\sstream"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\..\utility\arrayptr.h"\
	{$(INCLUDE)}"\..\utility\autores.h"\
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
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SSTREAM"\
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
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\sid.obj" : $(SOURCE) $(DEP_CPP_SID_C) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\sid.obj" : $(SOURCE) $(DEP_CPP_SID_C) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\sid.obj" : $(SOURCE) $(DEP_CPP_SID_C) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\io\src\bufdev.cpp
DEP_CPP_BUFDE=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\except\io.h"\
	{$(INCLUDE)}"\..\except\io.ipp"\
	{$(INCLUDE)}"\..\except\toolkit.h"\
	{$(INCLUDE)}"\..\except\toolkit.ipp"\
	{$(INCLUDE)}"\..\io\adapter.h"\
	{$(INCLUDE)}"\..\io\adapter.ipp"\
	{$(INCLUDE)}"\..\io\bufdev.h"\
	{$(INCLUDE)}"\..\io\bufdev.ipp"\
	{$(INCLUDE)}"\..\io\buffer.h"\
	{$(INCLUDE)}"\..\io\buffer.ipp"\
	{$(INCLUDE)}"\..\io\device.h"\
	{$(INCLUDE)}"\..\io\device.ipp"\
	{$(INCLUDE)}"\..\io\sid.h"\
	{$(INCLUDE)}"\..\io\types.h"\
	{$(INCLUDE)}"\..\std\iosfwd"\
	{$(INCLUDE)}"\..\std\iostream"\
	{$(INCLUDE)}"\..\type\prim.h"\
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
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\sys\TYPES.H"\
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
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\bufdev.obj" : $(SOURCE) $(DEP_CPP_BUFDE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\bufdev.obj" : $(SOURCE) $(DEP_CPP_BUFDE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\bufdev.obj" : $(SOURCE) $(DEP_CPP_BUFDE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\io\src\buffer.cpp
DEP_CPP_BUFFE=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\except\io.h"\
	{$(INCLUDE)}"\..\except\io.ipp"\
	{$(INCLUDE)}"\..\except\throw.h"\
	{$(INCLUDE)}"\..\except\toolkit.h"\
	{$(INCLUDE)}"\..\except\toolkit.ipp"\
	{$(INCLUDE)}"\..\internal\call.h"\
	{$(INCLUDE)}"\..\internal\errno.h"\
	{$(INCLUDE)}"\..\internal\error.h"\
	{$(INCLUDE)}"\..\internal\syscall.h"\
	{$(INCLUDE)}"\..\io\adapter.h"\
	{$(INCLUDE)}"\..\io\adapter.ipp"\
	{$(INCLUDE)}"\..\io\bufdev.h"\
	{$(INCLUDE)}"\..\io\bufdev.ipp"\
	{$(INCLUDE)}"\..\io\buffer.h"\
	{$(INCLUDE)}"\..\io\buffer.ipp"\
	{$(INCLUDE)}"\..\io\device.h"\
	{$(INCLUDE)}"\..\io\device.ipp"\
	{$(INCLUDE)}"\..\io\sid.h"\
	{$(INCLUDE)}"\..\io\types.h"\
	{$(INCLUDE)}"\..\std\iosfwd"\
	{$(INCLUDE)}"\..\std\iostream"\
	{$(INCLUDE)}"\..\std\sstream"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\..\utility\memory.h"\
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
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\sys\TYPES.H"\
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
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\buffer.obj" : $(SOURCE) $(DEP_CPP_BUFFE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\buffer.obj" : $(SOURCE) $(DEP_CPP_BUFFE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\buffer.obj" : $(SOURCE) $(DEP_CPP_BUFFE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\io\src\cache.cpp
DEP_CPP_CACHE=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\io\adapter.h"\
	{$(INCLUDE)}"\..\io\adapter.ipp"\
	{$(INCLUDE)}"\..\io\cache.h"\
	{$(INCLUDE)}"\..\io\cache.ipp"\
	{$(INCLUDE)}"\..\io\device.h"\
	{$(INCLUDE)}"\..\io\device.ipp"\
	{$(INCLUDE)}"\..\std\iosfwd"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\..\utility\memory.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\cache.obj" : $(SOURCE) $(DEP_CPP_CACHE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\cache.obj" : $(SOURCE) $(DEP_CPP_CACHE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\cache.obj" : $(SOURCE) $(DEP_CPP_CACHE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\io\src\device.cpp
DEP_CPP_DEVIC=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\io\device.h"\
	{$(INCLUDE)}"\..\io\device.ipp"\
	{$(INCLUDE)}"\..\std\iosfwd"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\device.obj" : $(SOURCE) $(DEP_CPP_DEVIC) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\device.obj" : $(SOURCE) $(DEP_CPP_DEVIC) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\device.obj" : $(SOURCE) $(DEP_CPP_DEVIC) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\io\src\iocontrl.cpp
DEP_CPP_IOCON=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\io\iocontrl.h"\
	{$(INCLUDE)}"\..\io\iocontrl.ipp"\
	{$(INCLUDE)}"\..\io\sid.h"\
	{$(INCLUDE)}"\..\io\types.h"\
	{$(INCLUDE)}"\..\std\iosfwd"\
	{$(INCLUDE)}"\..\std\iostream"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\..\utility\memory.h"\
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
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\sys\TYPES.H"\
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
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\iocontrl.obj" : $(SOURCE) $(DEP_CPP_IOCON) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\iocontrl.obj" : $(SOURCE) $(DEP_CPP_IOCON) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\iocontrl.obj" : $(SOURCE) $(DEP_CPP_IOCON) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\io\src\ioinit.cpp
DEP_CPP_IOINI=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\io\_startup.h"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\ioinit.obj" : $(SOURCE) $(DEP_CPP_IOINI) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\ioinit.obj" : $(SOURCE) $(DEP_CPP_IOINI) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\ioinit.obj" : $(SOURCE) $(DEP_CPP_IOINI) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\io\src\iostatus.cpp
DEP_CPP_IOSTA=\
	"..\utility\autoptr.org.h"\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\except\io.h"\
	{$(INCLUDE)}"\..\except\io.ipp"\
	{$(INCLUDE)}"\..\except\throw.h"\
	{$(INCLUDE)}"\..\except\toolkit.h"\
	{$(INCLUDE)}"\..\except\toolkit.ipp"\
	{$(INCLUDE)}"\..\extern.h"\
	{$(INCLUDE)}"\..\internal\call.h"\
	{$(INCLUDE)}"\..\internal\errno.h"\
	{$(INCLUDE)}"\..\internal\error.h"\
	{$(INCLUDE)}"\..\internal\fmacros.h"\
	{$(INCLUDE)}"\..\internal\syscall.h"\
	{$(INCLUDE)}"\..\io\iostatus.h"\
	{$(INCLUDE)}"\..\io\iostatus.ipp"\
	{$(INCLUDE)}"\..\io\sid.h"\
	{$(INCLUDE)}"\..\io\types.h"\
	{$(INCLUDE)}"\..\std\iosfwd"\
	{$(INCLUDE)}"\..\std\iostream"\
	{$(INCLUDE)}"\..\std\istream"\
	{$(INCLUDE)}"\..\std\ostream"\
	{$(INCLUDE)}"\..\std\sstream"\
	{$(INCLUDE)}"\..\std\string"\
	{$(INCLUDE)}"\..\stl\allocate.cc"\
	{$(INCLUDE)}"\..\stl\allocate.h"\
	{$(INCLUDE)}"\..\stl\allocimp.h"\
	{$(INCLUDE)}"\..\stl\common.h"\
	{$(INCLUDE)}"\..\stl\config.h"\
	{$(INCLUDE)}"\..\stl\iterator.cc"\
	{$(INCLUDE)}"\..\stl\iterator.h"\
	{$(INCLUDE)}"\..\stl\ops.h"\
	{$(INCLUDE)}"\..\stl\pair.h"\
	{$(INCLUDE)}"\..\stl\stlerror.h"\
	{$(INCLUDE)}"\..\string\basic.cc"\
	{$(INCLUDE)}"\..\string\basic.h"\
	{$(INCLUDE)}"\..\string\basic.ipp"\
	{$(INCLUDE)}"\..\string\config.h"\
	{$(INCLUDE)}"\..\string\search.cc"\
	{$(INCLUDE)}"\..\string\search.h"\
	{$(INCLUDE)}"\..\string\string.h"\
	{$(INCLUDE)}"\..\string\traits.cc"\
	{$(INCLUDE)}"\..\string\traits.h"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\..\utility\arrayptr.h"\
	{$(INCLUDE)}"\..\utility\autores.h"\
	{$(INCLUDE)}"\..\utility\memory.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\extern.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
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
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\iostatus.obj" : $(SOURCE) $(DEP_CPP_IOSTA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\iostatus.obj" : $(SOURCE) $(DEP_CPP_IOSTA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\iostatus.obj" : $(SOURCE) $(DEP_CPP_IOSTA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\io\src\openctrl.cpp
DEP_CPP_OPENC=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\io\openctrl.h"\
	{$(INCLUDE)}"\..\io\openctrl.ipp"\
	{$(INCLUDE)}"\..\io\sid.h"\
	{$(INCLUDE)}"\..\io\types.h"\
	{$(INCLUDE)}"\..\std\iosfwd"\
	{$(INCLUDE)}"\..\std\iostream"\
	{$(INCLUDE)}"\..\std\ostream"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\..\utility\memory.h"\
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
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\sys\TYPES.H"\
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
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\openctrl.obj" : $(SOURCE) $(DEP_CPP_OPENC) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\openctrl.obj" : $(SOURCE) $(DEP_CPP_OPENC) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\openctrl.obj" : $(SOURCE) $(DEP_CPP_OPENC) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\io\src\adapter.cpp
DEP_CPP_ADAPT=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\io\adapter.h"\
	{$(INCLUDE)}"\..\io\adapter.ipp"\
	{$(INCLUDE)}"\..\io\device.h"\
	{$(INCLUDE)}"\..\io\device.ipp"\
	{$(INCLUDE)}"\..\std\iosfwd"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\adapter.obj" : $(SOURCE) $(DEP_CPP_ADAPT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\adapter.obj" : $(SOURCE) $(DEP_CPP_ADAPT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\adapter.obj" : $(SOURCE) $(DEP_CPP_ADAPT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\except\src\io_ex.cpp
DEP_CPP_IO_EX=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\except\io.h"\
	{$(INCLUDE)}"\..\except\io.ipp"\
	{$(INCLUDE)}"\..\except\toolkit.h"\
	{$(INCLUDE)}"\..\except\toolkit.ipp"\
	{$(INCLUDE)}"\..\std\iostream"\
	{$(INCLUDE)}"\..\type\prim.h"\
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
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
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
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\io_ex.obj" : $(SOURCE) $(DEP_CPP_IO_EX) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\io_ex.obj" : $(SOURCE) $(DEP_CPP_IO_EX) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\io_ex.obj" : $(SOURCE) $(DEP_CPP_IO_EX) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\stream\src\tstream.cpp
DEP_CPP_TSTRE=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\io\adapter.h"\
	{$(INCLUDE)}"\..\io\adapter.ipp"\
	{$(INCLUDE)}"\..\std\iosfwd"\
	{$(INCLUDE)}"\..\std\istream"\
	{$(INCLUDE)}"\..\std\ostream"\
	{$(INCLUDE)}"\..\stream\strbuf.h"\
	{$(INCLUDE)}"\..\stream\strbuf.ipp"\
	{$(INCLUDE)}"\..\stream\tstream.h"\
	{$(INCLUDE)}"\..\stream\tstream.ipp"\
	{$(INCLUDE)}"\..\type\prim.h"\
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
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
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
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\tstream.obj" : $(SOURCE) $(DEP_CPP_TSTRE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\tstream.obj" : $(SOURCE) $(DEP_CPP_TSTRE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\tstream.obj" : $(SOURCE) $(DEP_CPP_TSTRE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\stream\src\bstream.cpp
DEP_CPP_BSTRE=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\except\config.h"\
	{$(INCLUDE)}"\..\except\except.h"\
	{$(INCLUDE)}"\..\except\stdex.h"\
	{$(INCLUDE)}"\..\except\stream.h"\
	{$(INCLUDE)}"\..\except\stream.ipp"\
	{$(INCLUDE)}"\..\except\throw.h"\
	{$(INCLUDE)}"\..\except\toolkit.h"\
	{$(INCLUDE)}"\..\except\toolkit.ipp"\
	{$(INCLUDE)}"\..\internal\call.h"\
	{$(INCLUDE)}"\..\internal\errno.h"\
	{$(INCLUDE)}"\..\internal\error.h"\
	{$(INCLUDE)}"\..\internal\fmacros.h"\
	{$(INCLUDE)}"\..\internal\syscall.h"\
	{$(INCLUDE)}"\..\io\adapter.h"\
	{$(INCLUDE)}"\..\io\adapter.ipp"\
	{$(INCLUDE)}"\..\io\buffer.h"\
	{$(INCLUDE)}"\..\io\buffer.ipp"\
	{$(INCLUDE)}"\..\io\sid.h"\
	{$(INCLUDE)}"\..\io\types.h"\
	{$(INCLUDE)}"\..\rtti\class.h"\
	{$(INCLUDE)}"\..\rtti\class.ipp"\
	{$(INCLUDE)}"\..\std\iosfwd"\
	{$(INCLUDE)}"\..\std\iostream"\
	{$(INCLUDE)}"\..\std\istream"\
	{$(INCLUDE)}"\..\std\map"\
	{$(INCLUDE)}"\..\std\ostream"\
	{$(INCLUDE)}"\..\std\sstream"\
	{$(INCLUDE)}"\..\std\string"\
	{$(INCLUDE)}"\..\std\typeinfo"\
	{$(INCLUDE)}"\..\std\vector"\
	{$(INCLUDE)}"\..\stl\allocate.cc"\
	{$(INCLUDE)}"\..\stl\allocate.h"\
	{$(INCLUDE)}"\..\stl\allocimp.h"\
	{$(INCLUDE)}"\..\stl\basalgo.cc"\
	{$(INCLUDE)}"\..\stl\basalgo.h"\
	{$(INCLUDE)}"\..\stl\common.h"\
	{$(INCLUDE)}"\..\stl\config.h"\
	{$(INCLUDE)}"\..\stl\function.h"\
	{$(INCLUDE)}"\..\stl\internal.h"\
	{$(INCLUDE)}"\..\stl\iterator.cc"\
	{$(INCLUDE)}"\..\stl\iterator.h"\
	{$(INCLUDE)}"\..\stl\map.cc"\
	{$(INCLUDE)}"\..\stl\map.h"\
	{$(INCLUDE)}"\..\stl\ops.h"\
	{$(INCLUDE)}"\..\stl\pair.h"\
	{$(INCLUDE)}"\..\stl\rawalgo.cc"\
	{$(INCLUDE)}"\..\stl\rawalgo.h"\
	{$(INCLUDE)}"\..\stl\rbtree.cc"\
	{$(INCLUDE)}"\..\stl\rbtree.h"\
	{$(INCLUDE)}"\..\stl\stlerror.h"\
	{$(INCLUDE)}"\..\stl\treeaux.h"\
	{$(INCLUDE)}"\..\stl\vector.cc"\
	{$(INCLUDE)}"\..\stl\vector.h"\
	{$(INCLUDE)}"\..\stream\bstream.h"\
	{$(INCLUDE)}"\..\stream\bstream.ipp"\
	{$(INCLUDE)}"\..\stream\ndr.h"\
	{$(INCLUDE)}"\..\stream\ndr.ipp"\
	{$(INCLUDE)}"\..\stream\ndrtypes.h"\
	{$(INCLUDE)}"\..\stream\protocol.h"\
	{$(INCLUDE)}"\..\stream\protocol.ipp"\
	{$(INCLUDE)}"\..\stream\strmaux.h"\
	{$(INCLUDE)}"\..\stream\strmaux.ipp"\
	{$(INCLUDE)}"\..\stream\strmmap.h"\
	{$(INCLUDE)}"\..\string\basic.cc"\
	{$(INCLUDE)}"\..\string\basic.h"\
	{$(INCLUDE)}"\..\string\basic.ipp"\
	{$(INCLUDE)}"\..\string\config.h"\
	{$(INCLUDE)}"\..\string\search.cc"\
	{$(INCLUDE)}"\..\string\search.h"\
	{$(INCLUDE)}"\..\string\string.h"\
	{$(INCLUDE)}"\..\string\traits.cc"\
	{$(INCLUDE)}"\..\string\traits.h"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\..\type\types.h"\
	{$(INCLUDE)}"\..\utility\memory.h"\
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
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
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
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\bstream.obj" : $(SOURCE) $(DEP_CPP_BSTRE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\bstream.obj" : $(SOURCE) $(DEP_CPP_BSTRE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\bstream.obj" : $(SOURCE) $(DEP_CPP_BSTRE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\stream\src\fstrmdev.cpp
DEP_CPP_FSTRM=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\io\adapter.h"\
	{$(INCLUDE)}"\..\io\adapter.ipp"\
	{$(INCLUDE)}"\..\io\device.h"\
	{$(INCLUDE)}"\..\io\device.ipp"\
	{$(INCLUDE)}"\..\std\fstream"\
	{$(INCLUDE)}"\..\std\iosfwd"\
	{$(INCLUDE)}"\..\stream\fstrmdev.h"\
	{$(INCLUDE)}"\..\stream\fstrmdev.ipp"\
	{$(INCLUDE)}"\..\type\prim.h"\
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
	{$(INCLUDE)}"\FSTREAM"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
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
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\fstrmdev.obj" : $(SOURCE) $(DEP_CPP_FSTRM) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\fstrmdev.obj" : $(SOURCE) $(DEP_CPP_FSTRM) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\fstrmdev.obj" : $(SOURCE) $(DEP_CPP_FSTRM) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\stream\src\istrmdev.cpp
DEP_CPP_ISTRM=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\io\adapter.h"\
	{$(INCLUDE)}"\..\io\adapter.ipp"\
	{$(INCLUDE)}"\..\io\device.h"\
	{$(INCLUDE)}"\..\io\device.ipp"\
	{$(INCLUDE)}"\..\std\iosfwd"\
	{$(INCLUDE)}"\..\std\istream"\
	{$(INCLUDE)}"\..\stream\istrmdev.h"\
	{$(INCLUDE)}"\..\stream\istrmdev.ipp"\
	{$(INCLUDE)}"\..\type\prim.h"\
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
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
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
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\istrmdev.obj" : $(SOURCE) $(DEP_CPP_ISTRM) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\istrmdev.obj" : $(SOURCE) $(DEP_CPP_ISTRM) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\istrmdev.obj" : $(SOURCE) $(DEP_CPP_ISTRM) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\stream\src\ndr.cpp
DEP_CPP_NDR_C=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\except\stream.h"\
	{$(INCLUDE)}"\..\except\stream.ipp"\
	{$(INCLUDE)}"\..\except\throw.h"\
	{$(INCLUDE)}"\..\except\toolkit.h"\
	{$(INCLUDE)}"\..\except\toolkit.ipp"\
	{$(INCLUDE)}"\..\internal\call.h"\
	{$(INCLUDE)}"\..\internal\errno.h"\
	{$(INCLUDE)}"\..\internal\error.h"\
	{$(INCLUDE)}"\..\internal\syscall.h"\
	{$(INCLUDE)}"\..\io\adapter.h"\
	{$(INCLUDE)}"\..\io\adapter.ipp"\
	{$(INCLUDE)}"\..\io\device.h"\
	{$(INCLUDE)}"\..\io\device.ipp"\
	{$(INCLUDE)}"\..\std\iosfwd"\
	{$(INCLUDE)}"\..\std\iostream"\
	{$(INCLUDE)}"\..\std\sstream"\
	{$(INCLUDE)}"\..\stream\ndr.h"\
	{$(INCLUDE)}"\..\stream\ndr.ipp"\
	{$(INCLUDE)}"\..\stream\ndrlabel.h"\
	{$(INCLUDE)}"\..\stream\ndrlabel.ipp"\
	{$(INCLUDE)}"\..\stream\ndrtypes.h"\
	{$(INCLUDE)}"\..\stream\protocol.h"\
	{$(INCLUDE)}"\..\stream\protocol.ipp"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\..\type\types.h"\
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
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SSTREAM"\
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
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\ndr.obj" : $(SOURCE) $(DEP_CPP_NDR_C) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\ndr.obj" : $(SOURCE) $(DEP_CPP_NDR_C) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\ndr.obj" : $(SOURCE) $(DEP_CPP_NDR_C) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\stream\src\ostrmdev.cpp
DEP_CPP_OSTRM=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\io\adapter.h"\
	{$(INCLUDE)}"\..\io\adapter.ipp"\
	{$(INCLUDE)}"\..\io\device.h"\
	{$(INCLUDE)}"\..\io\device.ipp"\
	{$(INCLUDE)}"\..\std\iosfwd"\
	{$(INCLUDE)}"\..\std\ostream"\
	{$(INCLUDE)}"\..\stream\ostrmdev.h"\
	{$(INCLUDE)}"\..\stream\ostrmdev.ipp"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\CERRNO"\
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
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
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
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\ostrmdev.obj" : $(SOURCE) $(DEP_CPP_OSTRM) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\ostrmdev.obj" : $(SOURCE) $(DEP_CPP_OSTRM) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\ostrmdev.obj" : $(SOURCE) $(DEP_CPP_OSTRM) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\stream\src\protocol.cpp
DEP_CPP_PROTO=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\io\adapter.h"\
	{$(INCLUDE)}"\..\io\adapter.ipp"\
	{$(INCLUDE)}"\..\io\device.h"\
	{$(INCLUDE)}"\..\io\device.ipp"\
	{$(INCLUDE)}"\..\std\iosfwd"\
	{$(INCLUDE)}"\..\stream\protocol.h"\
	{$(INCLUDE)}"\..\stream\protocol.ipp"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\..\type\types.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\protocol.obj" : $(SOURCE) $(DEP_CPP_PROTO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\protocol.obj" : $(SOURCE) $(DEP_CPP_PROTO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\protocol.obj" : $(SOURCE) $(DEP_CPP_PROTO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\stream\src\strbuf.cpp
DEP_CPP_STRBU=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\except\stream.h"\
	{$(INCLUDE)}"\..\except\stream.ipp"\
	{$(INCLUDE)}"\..\except\throw.h"\
	{$(INCLUDE)}"\..\except\toolkit.h"\
	{$(INCLUDE)}"\..\except\toolkit.ipp"\
	{$(INCLUDE)}"\..\internal\call.h"\
	{$(INCLUDE)}"\..\internal\errno.h"\
	{$(INCLUDE)}"\..\internal\error.h"\
	{$(INCLUDE)}"\..\internal\syscall.h"\
	{$(INCLUDE)}"\..\io\adapter.h"\
	{$(INCLUDE)}"\..\io\adapter.ipp"\
	{$(INCLUDE)}"\..\io\device.h"\
	{$(INCLUDE)}"\..\io\device.ipp"\
	{$(INCLUDE)}"\..\std\iosfwd"\
	{$(INCLUDE)}"\..\std\iostream"\
	{$(INCLUDE)}"\..\std\istream"\
	{$(INCLUDE)}"\..\std\ostream"\
	{$(INCLUDE)}"\..\std\sstream"\
	{$(INCLUDE)}"\..\stream\strbuf.h"\
	{$(INCLUDE)}"\..\stream\strbuf.ipp"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\..\utility\memory.h"\
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
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SSTREAM"\
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
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\strbuf.obj" : $(SOURCE) $(DEP_CPP_STRBU) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\strbuf.obj" : $(SOURCE) $(DEP_CPP_STRBU) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\strbuf.obj" : $(SOURCE) $(DEP_CPP_STRBU) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\stream\src\strmdev.cpp
DEP_CPP_STRMD=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\io\adapter.h"\
	{$(INCLUDE)}"\..\io\adapter.ipp"\
	{$(INCLUDE)}"\..\io\device.h"\
	{$(INCLUDE)}"\..\io\device.ipp"\
	{$(INCLUDE)}"\..\std\iosfwd"\
	{$(INCLUDE)}"\..\std\iostream"\
	{$(INCLUDE)}"\..\stream\strmdev.h"\
	{$(INCLUDE)}"\..\stream\strmdev.ipp"\
	{$(INCLUDE)}"\..\type\prim.h"\
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
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
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
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\strmdev.obj" : $(SOURCE) $(DEP_CPP_STRMD) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\strmdev.obj" : $(SOURCE) $(DEP_CPP_STRMD) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\strmdev.obj" : $(SOURCE) $(DEP_CPP_STRMD) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\stream\src\strminit.cpp
DEP_CPP_STRMI=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\strminit.obj" : $(SOURCE) $(DEP_CPP_STRMI) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\strminit.obj" : $(SOURCE) $(DEP_CPP_STRMI) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\strminit.obj" : $(SOURCE) $(DEP_CPP_STRMI) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\stream\src\ascii.cpp
DEP_CPP_ASCII=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\io\adapter.h"\
	{$(INCLUDE)}"\..\io\adapter.ipp"\
	{$(INCLUDE)}"\..\io\device.h"\
	{$(INCLUDE)}"\..\io\device.ipp"\
	{$(INCLUDE)}"\..\std\iosfwd"\
	{$(INCLUDE)}"\..\std\istream"\
	{$(INCLUDE)}"\..\std\ostream"\
	{$(INCLUDE)}"\..\stream\ascii.h"\
	{$(INCLUDE)}"\..\stream\protocol.h"\
	{$(INCLUDE)}"\..\stream\protocol.ipp"\
	{$(INCLUDE)}"\..\stream\strbuf.h"\
	{$(INCLUDE)}"\..\stream\strbuf.ipp"\
	{$(INCLUDE)}"\..\stream\tstream.h"\
	{$(INCLUDE)}"\..\stream\tstream.ipp"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\..\type\types.h"\
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
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
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
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\ascii.obj" : $(SOURCE) $(DEP_CPP_ASCII) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\ascii.obj" : $(SOURCE) $(DEP_CPP_ASCII) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\ascii.obj" : $(SOURCE) $(DEP_CPP_ASCII) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\rtti\src\classdb.cpp
DEP_CPP_CLASS=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\except\config.h"\
	{$(INCLUDE)}"\..\except\except.h"\
	{$(INCLUDE)}"\..\except\stdex.h"\
	{$(INCLUDE)}"\..\except\stream.h"\
	{$(INCLUDE)}"\..\except\stream.ipp"\
	{$(INCLUDE)}"\..\except\throw.h"\
	{$(INCLUDE)}"\..\except\toolkit.h"\
	{$(INCLUDE)}"\..\except\toolkit.ipp"\
	{$(INCLUDE)}"\..\internal\fmacros.h"\
	{$(INCLUDE)}"\..\rtti\cast.h"\
	{$(INCLUDE)}"\..\rtti\cast.ipp"\
	{$(INCLUDE)}"\..\rtti\class.h"\
	{$(INCLUDE)}"\..\rtti\class.ipp"\
	{$(INCLUDE)}"\..\rtti\classdb.h"\
	{$(INCLUDE)}"\..\rtti\info.h"\
	{$(INCLUDE)}"\..\std\algorithm"\
	{$(INCLUDE)}"\..\std\iosfwd"\
	{$(INCLUDE)}"\..\std\iostream"\
	{$(INCLUDE)}"\..\std\istream"\
	{$(INCLUDE)}"\..\std\map"\
	{$(INCLUDE)}"\..\std\ostream"\
	{$(INCLUDE)}"\..\std\sstream"\
	{$(INCLUDE)}"\..\std\string"\
	{$(INCLUDE)}"\..\std\typeinfo"\
	{$(INCLUDE)}"\..\std\vector"\
	{$(INCLUDE)}"\..\stl\advalgo.cc"\
	{$(INCLUDE)}"\..\stl\advalgo.h"\
	{$(INCLUDE)}"\..\stl\allocate.cc"\
	{$(INCLUDE)}"\..\stl\allocate.h"\
	{$(INCLUDE)}"\..\stl\allocimp.h"\
	{$(INCLUDE)}"\..\stl\auxalgo.cc"\
	{$(INCLUDE)}"\..\stl\auxalgo.h"\
	{$(INCLUDE)}"\..\stl\basalgo.cc"\
	{$(INCLUDE)}"\..\stl\basalgo.h"\
	{$(INCLUDE)}"\..\stl\common.h"\
	{$(INCLUDE)}"\..\stl\config.h"\
	{$(INCLUDE)}"\..\stl\function.h"\
	{$(INCLUDE)}"\..\stl\heap.cc"\
	{$(INCLUDE)}"\..\stl\heap.h"\
	{$(INCLUDE)}"\..\stl\internal.h"\
	{$(INCLUDE)}"\..\stl\iterator.cc"\
	{$(INCLUDE)}"\..\stl\iterator.h"\
	{$(INCLUDE)}"\..\stl\map.cc"\
	{$(INCLUDE)}"\..\stl\map.h"\
	{$(INCLUDE)}"\..\stl\ops.h"\
	{$(INCLUDE)}"\..\stl\pair.h"\
	{$(INCLUDE)}"\..\stl\randgen.h"\
	{$(INCLUDE)}"\..\stl\rawalgo.cc"\
	{$(INCLUDE)}"\..\stl\rawalgo.h"\
	{$(INCLUDE)}"\..\stl\rawiter.h"\
	{$(INCLUDE)}"\..\stl\rbtree.cc"\
	{$(INCLUDE)}"\..\stl\rbtree.h"\
	{$(INCLUDE)}"\..\stl\sort.cc"\
	{$(INCLUDE)}"\..\stl\sort.h"\
	{$(INCLUDE)}"\..\stl\stlerror.h"\
	{$(INCLUDE)}"\..\stl\tempbuf.cc"\
	{$(INCLUDE)}"\..\stl\tempbuf.h"\
	{$(INCLUDE)}"\..\stl\treeaux.h"\
	{$(INCLUDE)}"\..\stl\vector.cc"\
	{$(INCLUDE)}"\..\stl\vector.h"\
	{$(INCLUDE)}"\..\string\basic.cc"\
	{$(INCLUDE)}"\..\string\basic.h"\
	{$(INCLUDE)}"\..\string\basic.ipp"\
	{$(INCLUDE)}"\..\string\config.h"\
	{$(INCLUDE)}"\..\string\search.cc"\
	{$(INCLUDE)}"\..\string\search.h"\
	{$(INCLUDE)}"\..\string\string.h"\
	{$(INCLUDE)}"\..\string\traits.cc"\
	{$(INCLUDE)}"\..\string\traits.h"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\..\utility\memory.h"\
	{$(INCLUDE)}"\ALGORITHM"\
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
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
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
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\classdb.obj" : $(SOURCE) $(DEP_CPP_CLASS) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\classdb.obj" : $(SOURCE) $(DEP_CPP_CLASS) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\classdb.obj" : $(SOURCE) $(DEP_CPP_CLASS) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\rtti\src\class.cpp
DEP_CPP_CLASS_=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\except\config.h"\
	{$(INCLUDE)}"\..\except\except.h"\
	{$(INCLUDE)}"\..\except\stdex.h"\
	{$(INCLUDE)}"\..\except\stream.h"\
	{$(INCLUDE)}"\..\except\stream.ipp"\
	{$(INCLUDE)}"\..\except\throw.h"\
	{$(INCLUDE)}"\..\except\toolkit.h"\
	{$(INCLUDE)}"\..\except\toolkit.ipp"\
	{$(INCLUDE)}"\..\internal\fmacros.h"\
	{$(INCLUDE)}"\..\rtti\cast.h"\
	{$(INCLUDE)}"\..\rtti\cast.ipp"\
	{$(INCLUDE)}"\..\rtti\class.h"\
	{$(INCLUDE)}"\..\rtti\class.ipp"\
	{$(INCLUDE)}"\..\rtti\classdb.h"\
	{$(INCLUDE)}"\..\rtti\info.h"\
	{$(INCLUDE)}"\..\std\iosfwd"\
	{$(INCLUDE)}"\..\std\iostream"\
	{$(INCLUDE)}"\..\std\istream"\
	{$(INCLUDE)}"\..\std\map"\
	{$(INCLUDE)}"\..\std\ostream"\
	{$(INCLUDE)}"\..\std\sstream"\
	{$(INCLUDE)}"\..\std\string"\
	{$(INCLUDE)}"\..\std\typeinfo"\
	{$(INCLUDE)}"\..\std\utility"\
	{$(INCLUDE)}"\..\std\vector"\
	{$(INCLUDE)}"\..\stl\allocate.cc"\
	{$(INCLUDE)}"\..\stl\allocate.h"\
	{$(INCLUDE)}"\..\stl\allocimp.h"\
	{$(INCLUDE)}"\..\stl\basalgo.cc"\
	{$(INCLUDE)}"\..\stl\basalgo.h"\
	{$(INCLUDE)}"\..\stl\common.h"\
	{$(INCLUDE)}"\..\stl\config.h"\
	{$(INCLUDE)}"\..\stl\function.h"\
	{$(INCLUDE)}"\..\stl\internal.h"\
	{$(INCLUDE)}"\..\stl\iterator.cc"\
	{$(INCLUDE)}"\..\stl\iterator.h"\
	{$(INCLUDE)}"\..\stl\map.cc"\
	{$(INCLUDE)}"\..\stl\map.h"\
	{$(INCLUDE)}"\..\stl\ops.h"\
	{$(INCLUDE)}"\..\stl\pair.h"\
	{$(INCLUDE)}"\..\stl\rawalgo.cc"\
	{$(INCLUDE)}"\..\stl\rawalgo.h"\
	{$(INCLUDE)}"\..\stl\rbtree.cc"\
	{$(INCLUDE)}"\..\stl\rbtree.h"\
	{$(INCLUDE)}"\..\stl\stlerror.h"\
	{$(INCLUDE)}"\..\stl\treeaux.h"\
	{$(INCLUDE)}"\..\stl\vector.cc"\
	{$(INCLUDE)}"\..\stl\vector.h"\
	{$(INCLUDE)}"\..\string\basic.cc"\
	{$(INCLUDE)}"\..\string\basic.h"\
	{$(INCLUDE)}"\..\string\basic.ipp"\
	{$(INCLUDE)}"\..\string\config.h"\
	{$(INCLUDE)}"\..\string\search.cc"\
	{$(INCLUDE)}"\..\string\search.h"\
	{$(INCLUDE)}"\..\string\string.h"\
	{$(INCLUDE)}"\..\string\traits.cc"\
	{$(INCLUDE)}"\..\string\traits.h"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\..\utility\memory.h"\
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
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
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
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\class.obj" : $(SOURCE) $(DEP_CPP_CLASS_) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\class.obj" : $(SOURCE) $(DEP_CPP_CLASS_) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\class.obj" : $(SOURCE) $(DEP_CPP_CLASS_) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\rtti\src\cast.cpp
DEP_CPP_CAST_=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\rtti\cast.h"\
	{$(INCLUDE)}"\..\rtti\cast.ipp"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\cast.obj" : $(SOURCE) $(DEP_CPP_CAST_) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\cast.obj" : $(SOURCE) $(DEP_CPP_CAST_) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\cast.obj" : $(SOURCE) $(DEP_CPP_CAST_) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\except\src\stream_ex.cpp
DEP_CPP_STREA=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\except\stream.h"\
	{$(INCLUDE)}"\..\except\stream.ipp"\
	{$(INCLUDE)}"\..\except\toolkit.h"\
	{$(INCLUDE)}"\..\except\toolkit.ipp"\
	{$(INCLUDE)}"\..\std\iostream"\
	{$(INCLUDE)}"\..\type\prim.h"\
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
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
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
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\stream_ex.obj" : $(SOURCE) $(DEP_CPP_STREA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\stream_ex.obj" : $(SOURCE) $(DEP_CPP_STREA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\stream_ex.obj" : $(SOURCE) $(DEP_CPP_STREA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\thread\src\thread.cpp
DEP_CPP_THREA=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\except\config.h"\
	{$(INCLUDE)}"\..\except\except.h"\
	{$(INCLUDE)}"\..\except\stdex.h"\
	{$(INCLUDE)}"\..\except\thread.h"\
	{$(INCLUDE)}"\..\except\thread.ipp"\
	{$(INCLUDE)}"\..\except\throw.h"\
	{$(INCLUDE)}"\..\except\toolkit.h"\
	{$(INCLUDE)}"\..\except\toolkit.ipp"\
	{$(INCLUDE)}"\..\internal\call.h"\
	{$(INCLUDE)}"\..\internal\errno.h"\
	{$(INCLUDE)}"\..\internal\error.h"\
	{$(INCLUDE)}"\..\internal\fmacros.h"\
	{$(INCLUDE)}"\..\internal\syscall.h"\
	{$(INCLUDE)}"\..\std\iosfwd"\
	{$(INCLUDE)}"\..\std\iostream"\
	{$(INCLUDE)}"\..\std\istream"\
	{$(INCLUDE)}"\..\std\map"\
	{$(INCLUDE)}"\..\std\ostream"\
	{$(INCLUDE)}"\..\std\sstream"\
	{$(INCLUDE)}"\..\stl\allocate.cc"\
	{$(INCLUDE)}"\..\stl\allocate.h"\
	{$(INCLUDE)}"\..\stl\allocimp.h"\
	{$(INCLUDE)}"\..\stl\basalgo.cc"\
	{$(INCLUDE)}"\..\stl\basalgo.h"\
	{$(INCLUDE)}"\..\stl\common.h"\
	{$(INCLUDE)}"\..\stl\config.h"\
	{$(INCLUDE)}"\..\stl\function.h"\
	{$(INCLUDE)}"\..\stl\internal.h"\
	{$(INCLUDE)}"\..\stl\iterator.cc"\
	{$(INCLUDE)}"\..\stl\iterator.h"\
	{$(INCLUDE)}"\..\stl\map.cc"\
	{$(INCLUDE)}"\..\stl\map.h"\
	{$(INCLUDE)}"\..\stl\ops.h"\
	{$(INCLUDE)}"\..\stl\pair.h"\
	{$(INCLUDE)}"\..\stl\rbtree.cc"\
	{$(INCLUDE)}"\..\stl\rbtree.h"\
	{$(INCLUDE)}"\..\stl\stlerror.h"\
	{$(INCLUDE)}"\..\stl\treeaux.h"\
	{$(INCLUDE)}"\..\string\basic.cc"\
	{$(INCLUDE)}"\..\string\basic.h"\
	{$(INCLUDE)}"\..\string\basic.ipp"\
	{$(INCLUDE)}"\..\string\config.h"\
	{$(INCLUDE)}"\..\string\search.cc"\
	{$(INCLUDE)}"\..\string\search.h"\
	{$(INCLUDE)}"\..\string\string.h"\
	{$(INCLUDE)}"\..\string\traits.cc"\
	{$(INCLUDE)}"\..\string\traits.h"\
	{$(INCLUDE)}"\..\sync\eventsem.h"\
	{$(INCLUDE)}"\..\sync\eventsem.ipp"\
	{$(INCLUDE)}"\..\sync\mutex.h"\
	{$(INCLUDE)}"\..\sync\mutex.ipp"\
	{$(INCLUDE)}"\..\thread\_info.h"\
	{$(INCLUDE)}"\..\thread\_startup.h"\
	{$(INCLUDE)}"\..\thread\priority.h"\
	{$(INCLUDE)}"\..\thread\thisthrd.h"\
	{$(INCLUDE)}"\..\thread\thread.h"\
	{$(INCLUDE)}"\..\thread\thread.ipp"\
	{$(INCLUDE)}"\..\thread\types.h"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\..\utility\memory.h"\
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
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\sys\TYPES.H"\
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
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\thread.obj" : $(SOURCE) $(DEP_CPP_THREA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\thread.obj" : $(SOURCE) $(DEP_CPP_THREA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\thread.obj" : $(SOURCE) $(DEP_CPP_THREA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\thread\src\thisthrd.cpp
DEP_CPP_THIST=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\except\config.h"\
	{$(INCLUDE)}"\..\except\except.h"\
	{$(INCLUDE)}"\..\except\stdex.h"\
	{$(INCLUDE)}"\..\except\thread.h"\
	{$(INCLUDE)}"\..\except\thread.ipp"\
	{$(INCLUDE)}"\..\except\throw.h"\
	{$(INCLUDE)}"\..\except\toolkit.h"\
	{$(INCLUDE)}"\..\except\toolkit.ipp"\
	{$(INCLUDE)}"\..\extern.h"\
	{$(INCLUDE)}"\..\internal\call.h"\
	{$(INCLUDE)}"\..\internal\errno.h"\
	{$(INCLUDE)}"\..\internal\error.h"\
	{$(INCLUDE)}"\..\internal\fmacros.h"\
	{$(INCLUDE)}"\..\internal\syscall.h"\
	{$(INCLUDE)}"\..\std\iosfwd"\
	{$(INCLUDE)}"\..\std\iostream"\
	{$(INCLUDE)}"\..\std\istream"\
	{$(INCLUDE)}"\..\std\map"\
	{$(INCLUDE)}"\..\std\ostream"\
	{$(INCLUDE)}"\..\std\sstream"\
	{$(INCLUDE)}"\..\stl\allocate.cc"\
	{$(INCLUDE)}"\..\stl\allocate.h"\
	{$(INCLUDE)}"\..\stl\allocimp.h"\
	{$(INCLUDE)}"\..\stl\basalgo.cc"\
	{$(INCLUDE)}"\..\stl\basalgo.h"\
	{$(INCLUDE)}"\..\stl\common.h"\
	{$(INCLUDE)}"\..\stl\config.h"\
	{$(INCLUDE)}"\..\stl\function.h"\
	{$(INCLUDE)}"\..\stl\internal.h"\
	{$(INCLUDE)}"\..\stl\iterator.cc"\
	{$(INCLUDE)}"\..\stl\iterator.h"\
	{$(INCLUDE)}"\..\stl\map.cc"\
	{$(INCLUDE)}"\..\stl\map.h"\
	{$(INCLUDE)}"\..\stl\ops.h"\
	{$(INCLUDE)}"\..\stl\pair.h"\
	{$(INCLUDE)}"\..\stl\rbtree.cc"\
	{$(INCLUDE)}"\..\stl\rbtree.h"\
	{$(INCLUDE)}"\..\stl\stlerror.h"\
	{$(INCLUDE)}"\..\stl\treeaux.h"\
	{$(INCLUDE)}"\..\string\basic.cc"\
	{$(INCLUDE)}"\..\string\basic.h"\
	{$(INCLUDE)}"\..\string\basic.ipp"\
	{$(INCLUDE)}"\..\string\config.h"\
	{$(INCLUDE)}"\..\string\search.cc"\
	{$(INCLUDE)}"\..\string\search.h"\
	{$(INCLUDE)}"\..\string\string.h"\
	{$(INCLUDE)}"\..\string\traits.cc"\
	{$(INCLUDE)}"\..\string\traits.h"\
	{$(INCLUDE)}"\..\sync\eventsem.h"\
	{$(INCLUDE)}"\..\sync\eventsem.ipp"\
	{$(INCLUDE)}"\..\sync\mutex.h"\
	{$(INCLUDE)}"\..\sync\mutex.ipp"\
	{$(INCLUDE)}"\..\thread\_info.h"\
	{$(INCLUDE)}"\..\thread\_startup.h"\
	{$(INCLUDE)}"\..\thread\priority.h"\
	{$(INCLUDE)}"\..\thread\thisthrd.h"\
	{$(INCLUDE)}"\..\thread\thread.h"\
	{$(INCLUDE)}"\..\thread\thread.ipp"\
	{$(INCLUDE)}"\..\thread\types.h"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\..\utility\memory.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\extern.h"\
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
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
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
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\thisthrd.obj" : $(SOURCE) $(DEP_CPP_THIST) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\thisthrd.obj" : $(SOURCE) $(DEP_CPP_THIST) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\thisthrd.obj" : $(SOURCE) $(DEP_CPP_THIST) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\except\src\thread_ex.cpp
DEP_CPP_THREAD=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\except\thread.h"\
	{$(INCLUDE)}"\..\except\thread.ipp"\
	{$(INCLUDE)}"\..\except\toolkit.h"\
	{$(INCLUDE)}"\..\except\toolkit.ipp"\
	{$(INCLUDE)}"\..\std\iostream"\
	{$(INCLUDE)}"\..\type\prim.h"\
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
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
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
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\thread_ex.obj" : $(SOURCE) $(DEP_CPP_THREAD) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\thread_ex.obj" : $(SOURCE) $(DEP_CPP_THREAD) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\thread_ex.obj" : $(SOURCE) $(DEP_CPP_THREAD) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\sync\src\spriority.cpp
DEP_CPP_SPRIO=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\except\config.h"\
	{$(INCLUDE)}"\..\except\except.h"\
	{$(INCLUDE)}"\..\except\stdex.h"\
	{$(INCLUDE)}"\..\except\thread.h"\
	{$(INCLUDE)}"\..\except\thread.ipp"\
	{$(INCLUDE)}"\..\except\throw.h"\
	{$(INCLUDE)}"\..\except\toolkit.h"\
	{$(INCLUDE)}"\..\except\toolkit.ipp"\
	{$(INCLUDE)}"\..\internal\fmacros.h"\
	{$(INCLUDE)}"\..\std\iosfwd"\
	{$(INCLUDE)}"\..\std\iostream"\
	{$(INCLUDE)}"\..\std\istream"\
	{$(INCLUDE)}"\..\std\ostream"\
	{$(INCLUDE)}"\..\std\queue"\
	{$(INCLUDE)}"\..\std\sstream"\
	{$(INCLUDE)}"\..\std\vector"\
	{$(INCLUDE)}"\..\stl\allocate.cc"\
	{$(INCLUDE)}"\..\stl\allocate.h"\
	{$(INCLUDE)}"\..\stl\allocimp.h"\
	{$(INCLUDE)}"\..\stl\basalgo.cc"\
	{$(INCLUDE)}"\..\stl\basalgo.h"\
	{$(INCLUDE)}"\..\stl\common.h"\
	{$(INCLUDE)}"\..\stl\config.h"\
	{$(INCLUDE)}"\..\stl\function.h"\
	{$(INCLUDE)}"\..\stl\heap.cc"\
	{$(INCLUDE)}"\..\stl\heap.h"\
	{$(INCLUDE)}"\..\stl\iterator.cc"\
	{$(INCLUDE)}"\..\stl\iterator.h"\
	{$(INCLUDE)}"\..\stl\ops.h"\
	{$(INCLUDE)}"\..\stl\pair.h"\
	{$(INCLUDE)}"\..\stl\queue.h"\
	{$(INCLUDE)}"\..\stl\rawalgo.cc"\
	{$(INCLUDE)}"\..\stl\rawalgo.h"\
	{$(INCLUDE)}"\..\stl\stlerror.h"\
	{$(INCLUDE)}"\..\stl\vector.cc"\
	{$(INCLUDE)}"\..\stl\vector.h"\
	{$(INCLUDE)}"\..\string\basic.cc"\
	{$(INCLUDE)}"\..\string\basic.h"\
	{$(INCLUDE)}"\..\string\basic.ipp"\
	{$(INCLUDE)}"\..\string\config.h"\
	{$(INCLUDE)}"\..\string\search.cc"\
	{$(INCLUDE)}"\..\string\search.h"\
	{$(INCLUDE)}"\..\string\string.h"\
	{$(INCLUDE)}"\..\string\traits.cc"\
	{$(INCLUDE)}"\..\string\traits.h"\
	{$(INCLUDE)}"\..\sync\eventsem.h"\
	{$(INCLUDE)}"\..\sync\eventsem.ipp"\
	{$(INCLUDE)}"\..\sync\lock.h"\
	{$(INCLUDE)}"\..\sync\lock.ipp"\
	{$(INCLUDE)}"\..\sync\mutex.h"\
	{$(INCLUDE)}"\..\sync\mutex.ipp"\
	{$(INCLUDE)}"\..\sync\sprioimp.h"\
	{$(INCLUDE)}"\..\sync\spriority.h"\
	{$(INCLUDE)}"\..\thread\_startup.h"\
	{$(INCLUDE)}"\..\thread\priority.h"\
	{$(INCLUDE)}"\..\thread\thisthrd.h"\
	{$(INCLUDE)}"\..\thread\types.h"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\..\utility\memory.h"\
	{$(INCLUDE)}"\ALGORITHM"\
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
	{$(INCLUDE)}"\DEQUE"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\QUEUE"\
	{$(INCLUDE)}"\SSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
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
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\spriority.obj" : $(SOURCE) $(DEP_CPP_SPRIO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\spriority.obj" : $(SOURCE) $(DEP_CPP_SPRIO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\spriority.obj" : $(SOURCE) $(DEP_CPP_SPRIO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\sync\src\critical.cpp
DEP_CPP_CRITI=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\std\iosfwd"\
	{$(INCLUDE)}"\..\std\ostream"\
	{$(INCLUDE)}"\..\sync\critical.h"\
	{$(INCLUDE)}"\..\sync\critical.ipp"\
	{$(INCLUDE)}"\..\sync\mutex.h"\
	{$(INCLUDE)}"\..\sync\mutex.ipp"\
	{$(INCLUDE)}"\..\thread\_startup.h"\
	{$(INCLUDE)}"\..\thread\priority.h"\
	{$(INCLUDE)}"\..\thread\thisthrd.h"\
	{$(INCLUDE)}"\..\thread\types.h"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\..\utility\memory.h"\
	{$(INCLUDE)}"\CERRNO"\
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
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\sys\TYPES.H"\
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
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\critical.obj" : $(SOURCE) $(DEP_CPP_CRITI) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\critical.obj" : $(SOURCE) $(DEP_CPP_CRITI) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\critical.obj" : $(SOURCE) $(DEP_CPP_CRITI) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\sync\src\eventsem.cpp
DEP_CPP_EVENT=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\except\thread.h"\
	{$(INCLUDE)}"\..\except\thread.ipp"\
	{$(INCLUDE)}"\..\except\toolkit.h"\
	{$(INCLUDE)}"\..\except\toolkit.ipp"\
	{$(INCLUDE)}"\..\internal\call.h"\
	{$(INCLUDE)}"\..\internal\errno.h"\
	{$(INCLUDE)}"\..\internal\error.h"\
	{$(INCLUDE)}"\..\internal\syscall.h"\
	{$(INCLUDE)}"\..\std\iosfwd"\
	{$(INCLUDE)}"\..\std\iostream"\
	{$(INCLUDE)}"\..\std\ostream"\
	{$(INCLUDE)}"\..\std\sstream"\
	{$(INCLUDE)}"\..\sync\eventsem.h"\
	{$(INCLUDE)}"\..\sync\eventsem.ipp"\
	{$(INCLUDE)}"\..\sync\lock.h"\
	{$(INCLUDE)}"\..\sync\lock.ipp"\
	{$(INCLUDE)}"\..\sync\mutex.h"\
	{$(INCLUDE)}"\..\sync\mutex.ipp"\
	{$(INCLUDE)}"\..\thread\_startup.h"\
	{$(INCLUDE)}"\..\thread\priority.h"\
	{$(INCLUDE)}"\..\thread\thisthrd.h"\
	{$(INCLUDE)}"\..\thread\types.h"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\..\utility\memory.h"\
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
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\sys\TYPES.H"\
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
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\eventsem.obj" : $(SOURCE) $(DEP_CPP_EVENT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\eventsem.obj" : $(SOURCE) $(DEP_CPP_EVENT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\eventsem.obj" : $(SOURCE) $(DEP_CPP_EVENT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\sync\src\mutex.cpp
DEP_CPP_MUTEX=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\except\thread.h"\
	{$(INCLUDE)}"\..\except\thread.ipp"\
	{$(INCLUDE)}"\..\except\throw.h"\
	{$(INCLUDE)}"\..\except\toolkit.h"\
	{$(INCLUDE)}"\..\except\toolkit.ipp"\
	{$(INCLUDE)}"\..\internal\call.h"\
	{$(INCLUDE)}"\..\internal\errno.h"\
	{$(INCLUDE)}"\..\internal\error.h"\
	{$(INCLUDE)}"\..\internal\syscall.h"\
	{$(INCLUDE)}"\..\std\iosfwd"\
	{$(INCLUDE)}"\..\std\iostream"\
	{$(INCLUDE)}"\..\std\ostream"\
	{$(INCLUDE)}"\..\std\sstream"\
	{$(INCLUDE)}"\..\sync\mutex.h"\
	{$(INCLUDE)}"\..\sync\mutex.ipp"\
	{$(INCLUDE)}"\..\thread\_startup.h"\
	{$(INCLUDE)}"\..\thread\priority.h"\
	{$(INCLUDE)}"\..\thread\thisthrd.h"\
	{$(INCLUDE)}"\..\thread\types.h"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\..\utility\memory.h"\
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
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\sys\TYPES.H"\
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
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\mutex.obj" : $(SOURCE) $(DEP_CPP_MUTEX) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\mutex.obj" : $(SOURCE) $(DEP_CPP_MUTEX) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\mutex.obj" : $(SOURCE) $(DEP_CPP_MUTEX) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\sync\src\rfifo.cpp
DEP_CPP_RFIFO=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\except\config.h"\
	{$(INCLUDE)}"\..\except\except.h"\
	{$(INCLUDE)}"\..\except\stdex.h"\
	{$(INCLUDE)}"\..\except\thread.h"\
	{$(INCLUDE)}"\..\except\thread.ipp"\
	{$(INCLUDE)}"\..\except\throw.h"\
	{$(INCLUDE)}"\..\except\toolkit.h"\
	{$(INCLUDE)}"\..\except\toolkit.ipp"\
	{$(INCLUDE)}"\..\internal\fmacros.h"\
	{$(INCLUDE)}"\..\std\iosfwd"\
	{$(INCLUDE)}"\..\std\iostream"\
	{$(INCLUDE)}"\..\std\istream"\
	{$(INCLUDE)}"\..\std\list"\
	{$(INCLUDE)}"\..\std\ostream"\
	{$(INCLUDE)}"\..\std\sstream"\
	{$(INCLUDE)}"\..\stl\allocate.cc"\
	{$(INCLUDE)}"\..\stl\allocate.h"\
	{$(INCLUDE)}"\..\stl\allocimp.h"\
	{$(INCLUDE)}"\..\stl\basalgo.cc"\
	{$(INCLUDE)}"\..\stl\basalgo.h"\
	{$(INCLUDE)}"\..\stl\common.h"\
	{$(INCLUDE)}"\..\stl\config.h"\
	{$(INCLUDE)}"\..\stl\function.h"\
	{$(INCLUDE)}"\..\stl\iterator.cc"\
	{$(INCLUDE)}"\..\stl\iterator.h"\
	{$(INCLUDE)}"\..\stl\list.cc"\
	{$(INCLUDE)}"\..\stl\list.h"\
	{$(INCLUDE)}"\..\stl\nodealoc.cc"\
	{$(INCLUDE)}"\..\stl\nodealoc.h"\
	{$(INCLUDE)}"\..\stl\ops.h"\
	{$(INCLUDE)}"\..\stl\pair.h"\
	{$(INCLUDE)}"\..\stl\stlerror.h"\
	{$(INCLUDE)}"\..\string\basic.cc"\
	{$(INCLUDE)}"\..\string\basic.h"\
	{$(INCLUDE)}"\..\string\basic.ipp"\
	{$(INCLUDE)}"\..\string\config.h"\
	{$(INCLUDE)}"\..\string\search.cc"\
	{$(INCLUDE)}"\..\string\search.h"\
	{$(INCLUDE)}"\..\string\string.h"\
	{$(INCLUDE)}"\..\string\traits.cc"\
	{$(INCLUDE)}"\..\string\traits.h"\
	{$(INCLUDE)}"\..\sync\eventsem.h"\
	{$(INCLUDE)}"\..\sync\eventsem.ipp"\
	{$(INCLUDE)}"\..\sync\lock.h"\
	{$(INCLUDE)}"\..\sync\lock.ipp"\
	{$(INCLUDE)}"\..\sync\mutex.h"\
	{$(INCLUDE)}"\..\sync\mutex.ipp"\
	{$(INCLUDE)}"\..\sync\rfifo.h"\
	{$(INCLUDE)}"\..\sync\rfifoimp.h"\
	{$(INCLUDE)}"\..\thread\_startup.h"\
	{$(INCLUDE)}"\..\thread\priority.h"\
	{$(INCLUDE)}"\..\thread\thisthrd.h"\
	{$(INCLUDE)}"\..\thread\types.h"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\..\utility\memory.h"\
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
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\sys\TYPES.H"\
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
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\rfifo.obj" : $(SOURCE) $(DEP_CPP_RFIFO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\rfifo.obj" : $(SOURCE) $(DEP_CPP_RFIFO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\rfifo.obj" : $(SOURCE) $(DEP_CPP_RFIFO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\sync\src\rpriority.cpp
DEP_CPP_RPRIO=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\except\config.h"\
	{$(INCLUDE)}"\..\except\except.h"\
	{$(INCLUDE)}"\..\except\stdex.h"\
	{$(INCLUDE)}"\..\except\thread.h"\
	{$(INCLUDE)}"\..\except\thread.ipp"\
	{$(INCLUDE)}"\..\except\throw.h"\
	{$(INCLUDE)}"\..\except\toolkit.h"\
	{$(INCLUDE)}"\..\except\toolkit.ipp"\
	{$(INCLUDE)}"\..\internal\fmacros.h"\
	{$(INCLUDE)}"\..\std\iosfwd"\
	{$(INCLUDE)}"\..\std\iostream"\
	{$(INCLUDE)}"\..\std\istream"\
	{$(INCLUDE)}"\..\std\ostream"\
	{$(INCLUDE)}"\..\std\queue"\
	{$(INCLUDE)}"\..\std\sstream"\
	{$(INCLUDE)}"\..\std\vector"\
	{$(INCLUDE)}"\..\stl\allocate.cc"\
	{$(INCLUDE)}"\..\stl\allocate.h"\
	{$(INCLUDE)}"\..\stl\allocimp.h"\
	{$(INCLUDE)}"\..\stl\basalgo.cc"\
	{$(INCLUDE)}"\..\stl\basalgo.h"\
	{$(INCLUDE)}"\..\stl\common.h"\
	{$(INCLUDE)}"\..\stl\config.h"\
	{$(INCLUDE)}"\..\stl\function.h"\
	{$(INCLUDE)}"\..\stl\heap.cc"\
	{$(INCLUDE)}"\..\stl\heap.h"\
	{$(INCLUDE)}"\..\stl\iterator.cc"\
	{$(INCLUDE)}"\..\stl\iterator.h"\
	{$(INCLUDE)}"\..\stl\ops.h"\
	{$(INCLUDE)}"\..\stl\pair.h"\
	{$(INCLUDE)}"\..\stl\queue.h"\
	{$(INCLUDE)}"\..\stl\rawalgo.cc"\
	{$(INCLUDE)}"\..\stl\rawalgo.h"\
	{$(INCLUDE)}"\..\stl\stlerror.h"\
	{$(INCLUDE)}"\..\stl\vector.cc"\
	{$(INCLUDE)}"\..\stl\vector.h"\
	{$(INCLUDE)}"\..\string\basic.cc"\
	{$(INCLUDE)}"\..\string\basic.h"\
	{$(INCLUDE)}"\..\string\basic.ipp"\
	{$(INCLUDE)}"\..\string\config.h"\
	{$(INCLUDE)}"\..\string\search.cc"\
	{$(INCLUDE)}"\..\string\search.h"\
	{$(INCLUDE)}"\..\string\string.h"\
	{$(INCLUDE)}"\..\string\traits.cc"\
	{$(INCLUDE)}"\..\string\traits.h"\
	{$(INCLUDE)}"\..\sync\eventsem.h"\
	{$(INCLUDE)}"\..\sync\eventsem.ipp"\
	{$(INCLUDE)}"\..\sync\lock.h"\
	{$(INCLUDE)}"\..\sync\lock.ipp"\
	{$(INCLUDE)}"\..\sync\mutex.h"\
	{$(INCLUDE)}"\..\sync\mutex.ipp"\
	{$(INCLUDE)}"\..\sync\rprioimp.h"\
	{$(INCLUDE)}"\..\sync\rpriority.h"\
	{$(INCLUDE)}"\..\thread\_startup.h"\
	{$(INCLUDE)}"\..\thread\priority.h"\
	{$(INCLUDE)}"\..\thread\thisthrd.h"\
	{$(INCLUDE)}"\..\thread\types.h"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\..\utility\memory.h"\
	{$(INCLUDE)}"\ALGORITHM"\
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
	{$(INCLUDE)}"\DEQUE"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\QUEUE"\
	{$(INCLUDE)}"\SSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
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
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\rpriority.obj" : $(SOURCE) $(DEP_CPP_RPRIO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\rpriority.obj" : $(SOURCE) $(DEP_CPP_RPRIO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\rpriority.obj" : $(SOURCE) $(DEP_CPP_RPRIO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\sync\src\rwsem.cpp
DEP_CPP_RWSEM=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\std\iosfwd"\
	{$(INCLUDE)}"\..\std\ostream"\
	{$(INCLUDE)}"\..\sync\eventsem.h"\
	{$(INCLUDE)}"\..\sync\eventsem.ipp"\
	{$(INCLUDE)}"\..\sync\lock.h"\
	{$(INCLUDE)}"\..\sync\lock.ipp"\
	{$(INCLUDE)}"\..\sync\mutex.h"\
	{$(INCLUDE)}"\..\sync\mutex.ipp"\
	{$(INCLUDE)}"\..\sync\rwsem.h"\
	{$(INCLUDE)}"\..\sync\rwsem.ipp"\
	{$(INCLUDE)}"\..\thread\_startup.h"\
	{$(INCLUDE)}"\..\thread\priority.h"\
	{$(INCLUDE)}"\..\thread\thisthrd.h"\
	{$(INCLUDE)}"\..\thread\types.h"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\..\utility\memory.h"\
	{$(INCLUDE)}"\CERRNO"\
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
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\sys\TYPES.H"\
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
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\rwsem.obj" : $(SOURCE) $(DEP_CPP_RWSEM) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\rwsem.obj" : $(SOURCE) $(DEP_CPP_RWSEM) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\rwsem.obj" : $(SOURCE) $(DEP_CPP_RWSEM) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\sync\src\sfifo.cpp
DEP_CPP_SFIFO=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\except\config.h"\
	{$(INCLUDE)}"\..\except\except.h"\
	{$(INCLUDE)}"\..\except\stdex.h"\
	{$(INCLUDE)}"\..\except\thread.h"\
	{$(INCLUDE)}"\..\except\thread.ipp"\
	{$(INCLUDE)}"\..\except\throw.h"\
	{$(INCLUDE)}"\..\except\toolkit.h"\
	{$(INCLUDE)}"\..\except\toolkit.ipp"\
	{$(INCLUDE)}"\..\internal\fmacros.h"\
	{$(INCLUDE)}"\..\std\iosfwd"\
	{$(INCLUDE)}"\..\std\iostream"\
	{$(INCLUDE)}"\..\std\istream"\
	{$(INCLUDE)}"\..\std\list"\
	{$(INCLUDE)}"\..\std\ostream"\
	{$(INCLUDE)}"\..\std\sstream"\
	{$(INCLUDE)}"\..\stl\allocate.cc"\
	{$(INCLUDE)}"\..\stl\allocate.h"\
	{$(INCLUDE)}"\..\stl\allocimp.h"\
	{$(INCLUDE)}"\..\stl\basalgo.cc"\
	{$(INCLUDE)}"\..\stl\basalgo.h"\
	{$(INCLUDE)}"\..\stl\common.h"\
	{$(INCLUDE)}"\..\stl\config.h"\
	{$(INCLUDE)}"\..\stl\function.h"\
	{$(INCLUDE)}"\..\stl\iterator.cc"\
	{$(INCLUDE)}"\..\stl\iterator.h"\
	{$(INCLUDE)}"\..\stl\list.cc"\
	{$(INCLUDE)}"\..\stl\list.h"\
	{$(INCLUDE)}"\..\stl\nodealoc.cc"\
	{$(INCLUDE)}"\..\stl\nodealoc.h"\
	{$(INCLUDE)}"\..\stl\ops.h"\
	{$(INCLUDE)}"\..\stl\pair.h"\
	{$(INCLUDE)}"\..\stl\stlerror.h"\
	{$(INCLUDE)}"\..\string\basic.cc"\
	{$(INCLUDE)}"\..\string\basic.h"\
	{$(INCLUDE)}"\..\string\basic.ipp"\
	{$(INCLUDE)}"\..\string\config.h"\
	{$(INCLUDE)}"\..\string\search.cc"\
	{$(INCLUDE)}"\..\string\search.h"\
	{$(INCLUDE)}"\..\string\string.h"\
	{$(INCLUDE)}"\..\string\traits.cc"\
	{$(INCLUDE)}"\..\string\traits.h"\
	{$(INCLUDE)}"\..\sync\eventsem.h"\
	{$(INCLUDE)}"\..\sync\eventsem.ipp"\
	{$(INCLUDE)}"\..\sync\lock.h"\
	{$(INCLUDE)}"\..\sync\lock.ipp"\
	{$(INCLUDE)}"\..\sync\mutex.h"\
	{$(INCLUDE)}"\..\sync\mutex.ipp"\
	{$(INCLUDE)}"\..\sync\sfifo.h"\
	{$(INCLUDE)}"\..\sync\sfifoimp.h"\
	{$(INCLUDE)}"\..\thread\_startup.h"\
	{$(INCLUDE)}"\..\thread\priority.h"\
	{$(INCLUDE)}"\..\thread\thisthrd.h"\
	{$(INCLUDE)}"\..\thread\types.h"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\..\utility\memory.h"\
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
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\sys\TYPES.H"\
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
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\sfifo.obj" : $(SOURCE) $(DEP_CPP_SFIFO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\sfifo.obj" : $(SOURCE) $(DEP_CPP_SFIFO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\sfifo.obj" : $(SOURCE) $(DEP_CPP_SFIFO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\sync\src\smutex.cpp
DEP_CPP_SMUTE=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\std\iosfwd"\
	{$(INCLUDE)}"\..\std\ostream"\
	{$(INCLUDE)}"\..\sync\mutex.h"\
	{$(INCLUDE)}"\..\sync\mutex.ipp"\
	{$(INCLUDE)}"\..\sync\simple.h"\
	{$(INCLUDE)}"\..\thread\_startup.h"\
	{$(INCLUDE)}"\..\thread\priority.h"\
	{$(INCLUDE)}"\..\thread\thisthrd.h"\
	{$(INCLUDE)}"\..\thread\types.h"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\..\utility\memory.h"\
	{$(INCLUDE)}"\CERRNO"\
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
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\sys\TYPES.H"\
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
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\smutex.obj" : $(SOURCE) $(DEP_CPP_SMUTE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\smutex.obj" : $(SOURCE) $(DEP_CPP_SMUTE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\smutex.obj" : $(SOURCE) $(DEP_CPP_SMUTE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\sync\src\counting.cpp
DEP_CPP_COUNT=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\except\thread.h"\
	{$(INCLUDE)}"\..\except\thread.ipp"\
	{$(INCLUDE)}"\..\except\throw.h"\
	{$(INCLUDE)}"\..\except\toolkit.h"\
	{$(INCLUDE)}"\..\except\toolkit.ipp"\
	{$(INCLUDE)}"\..\std\iosfwd"\
	{$(INCLUDE)}"\..\std\iostream"\
	{$(INCLUDE)}"\..\std\ostream"\
	{$(INCLUDE)}"\..\std\sstream"\
	{$(INCLUDE)}"\..\sync\counting.h"\
	{$(INCLUDE)}"\..\sync\counting.ipp"\
	{$(INCLUDE)}"\..\sync\eventsem.h"\
	{$(INCLUDE)}"\..\sync\eventsem.ipp"\
	{$(INCLUDE)}"\..\sync\lock.h"\
	{$(INCLUDE)}"\..\sync\lock.ipp"\
	{$(INCLUDE)}"\..\sync\mutex.h"\
	{$(INCLUDE)}"\..\sync\mutex.ipp"\
	{$(INCLUDE)}"\..\thread\_startup.h"\
	{$(INCLUDE)}"\..\thread\priority.h"\
	{$(INCLUDE)}"\..\thread\thisthrd.h"\
	{$(INCLUDE)}"\..\thread\types.h"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\..\utility\memory.h"\
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
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\sys\TYPES.H"\
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
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\counting.obj" : $(SOURCE) $(DEP_CPP_COUNT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\counting.obj" : $(SOURCE) $(DEP_CPP_COUNT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\counting.obj" : $(SOURCE) $(DEP_CPP_COUNT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OSPACED.DEF

!IF  "$(CFG)" == "standards - Win32 MT Debug"

!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OSPACE.DEF

!IF  "$(CFG)" == "standards - Win32 MT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"

!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"

# PROP Exclude_From_Build 0

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\COM\SRC\OOLESTRM.CPP
DEP_CPP_OOLES=\
	{$(INCLUDE)}"\..\com\olestrea.h"\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\olestrea.h"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\OOLESTRM.OBJ" : $(SOURCE) $(DEP_CPP_OOLES) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\OOLESTRM.OBJ" : $(SOURCE) $(DEP_CPP_OOLES) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\OOLESTRM.OBJ" : $(SOURCE) $(DEP_CPP_OOLES) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\COM\SRC\OLEBUF.CPP
DEP_CPP_OLEBU=\
	{$(INCLUDE)}"\..\com\olestrea.h"\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\olestrea.h"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\OLEBUF.OBJ" : $(SOURCE) $(DEP_CPP_OLEBU) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\OLEBUF.OBJ" : $(SOURCE) $(DEP_CPP_OLEBU) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\OLEBUF.OBJ" : $(SOURCE) $(DEP_CPP_OLEBU) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\COM\SRC\OLEBUF1.CPP
DEP_CPP_OLEBUF=\
	{$(INCLUDE)}"\..\com\olestrea.h"\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\olestrea.h"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\OLEBUF1.OBJ" : $(SOURCE) $(DEP_CPP_OLEBUF) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\OLEBUF1.OBJ" : $(SOURCE) $(DEP_CPP_OLEBUF) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\OLEBUF1.OBJ" : $(SOURCE) $(DEP_CPP_OLEBUF) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\COM\SRC\OLESTREA.CPP
DEP_CPP_OLEST=\
	{$(INCLUDE)}"\..\com\olestrea.h"\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\olestrea.h"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\OLESTREA.OBJ" : $(SOURCE) $(DEP_CPP_OLEST) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\OLESTREA.OBJ" : $(SOURCE) $(DEP_CPP_OLEST) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\OLESTREA.OBJ" : $(SOURCE) $(DEP_CPP_OLEST) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\COM\SRC\IOLESTRM.CPP
DEP_CPP_IOLES=\
	{$(INCLUDE)}"\..\com\olestrea.h"\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\olestrea.h"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\IOLESTRM.OBJ" : $(SOURCE) $(DEP_CPP_IOLES) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\IOLESTRM.OBJ" : $(SOURCE) $(DEP_CPP_IOLES) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\IOLESTRM.OBJ" : $(SOURCE) $(DEP_CPP_IOLES) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\file\src\path.cpp
DEP_CPP_PATH_=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\except\file.h"\
	{$(INCLUDE)}"\..\except\file.ipp"\
	{$(INCLUDE)}"\..\except\throw.h"\
	{$(INCLUDE)}"\..\except\toolkit.h"\
	{$(INCLUDE)}"\..\except\toolkit.ipp"\
	{$(INCLUDE)}"\..\file\path.h"\
	{$(INCLUDE)}"\..\file\path.ipp"\
	{$(INCLUDE)}"\..\internal\call.h"\
	{$(INCLUDE)}"\..\internal\errno.h"\
	{$(INCLUDE)}"\..\internal\error.h"\
	{$(INCLUDE)}"\..\internal\fmacros.h"\
	{$(INCLUDE)}"\..\internal\syscall.h"\
	{$(INCLUDE)}"\..\std\iosfwd"\
	{$(INCLUDE)}"\..\std\iostream"\
	{$(INCLUDE)}"\..\std\istream"\
	{$(INCLUDE)}"\..\std\ostream"\
	{$(INCLUDE)}"\..\std\sstream"\
	{$(INCLUDE)}"\..\std\string"\
	{$(INCLUDE)}"\..\stl\allocate.cc"\
	{$(INCLUDE)}"\..\stl\allocate.h"\
	{$(INCLUDE)}"\..\stl\allocimp.h"\
	{$(INCLUDE)}"\..\stl\common.h"\
	{$(INCLUDE)}"\..\stl\config.h"\
	{$(INCLUDE)}"\..\stl\iterator.cc"\
	{$(INCLUDE)}"\..\stl\iterator.h"\
	{$(INCLUDE)}"\..\stl\ops.h"\
	{$(INCLUDE)}"\..\stl\pair.h"\
	{$(INCLUDE)}"\..\stl\stlerror.h"\
	{$(INCLUDE)}"\..\string\basic.cc"\
	{$(INCLUDE)}"\..\string\basic.h"\
	{$(INCLUDE)}"\..\string\basic.ipp"\
	{$(INCLUDE)}"\..\string\config.h"\
	{$(INCLUDE)}"\..\string\search.cc"\
	{$(INCLUDE)}"\..\string\search.h"\
	{$(INCLUDE)}"\..\string\string.h"\
	{$(INCLUDE)}"\..\string\traits.cc"\
	{$(INCLUDE)}"\..\string\traits.h"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\..\utility\memory.h"\
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
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SSTREAM"\
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
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\path.obj" : $(SOURCE) $(DEP_CPP_PATH_) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\path.obj" : $(SOURCE) $(DEP_CPP_PATH_) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\path.obj" : $(SOURCE) $(DEP_CPP_PATH_) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\file\src\file.cpp
DEP_CPP_FILE_=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\except\file.h"\
	{$(INCLUDE)}"\..\except\file.ipp"\
	{$(INCLUDE)}"\..\except\io.h"\
	{$(INCLUDE)}"\..\except\io.ipp"\
	{$(INCLUDE)}"\..\except\throw.h"\
	{$(INCLUDE)}"\..\except\toolkit.h"\
	{$(INCLUDE)}"\..\except\toolkit.ipp"\
	{$(INCLUDE)}"\..\extern.h"\
	{$(INCLUDE)}"\..\file\file.h"\
	{$(INCLUDE)}"\..\file\file.ipp"\
	{$(INCLUDE)}"\..\file\filedev.h"\
	{$(INCLUDE)}"\..\file\filedev.ipp"\
	{$(INCLUDE)}"\..\file\filelock.h"\
	{$(INCLUDE)}"\..\file\filelock.ipp"\
	{$(INCLUDE)}"\..\internal\call.h"\
	{$(INCLUDE)}"\..\internal\errno.h"\
	{$(INCLUDE)}"\..\internal\error.h"\
	{$(INCLUDE)}"\..\internal\fmacros.h"\
	{$(INCLUDE)}"\..\internal\syscall.h"\
	{$(INCLUDE)}"\..\io.h"\
	{$(INCLUDE)}"\..\io\_startup.h"\
	{$(INCLUDE)}"\..\io\adapter.h"\
	{$(INCLUDE)}"\..\io\adapter.ipp"\
	{$(INCLUDE)}"\..\io\bufdev.h"\
	{$(INCLUDE)}"\..\io\bufdev.ipp"\
	{$(INCLUDE)}"\..\io\buffer.h"\
	{$(INCLUDE)}"\..\io\buffer.ipp"\
	{$(INCLUDE)}"\..\io\cache.h"\
	{$(INCLUDE)}"\..\io\cache.ipp"\
	{$(INCLUDE)}"\..\io\device.h"\
	{$(INCLUDE)}"\..\io\device.ipp"\
	{$(INCLUDE)}"\..\io\iocontrl.h"\
	{$(INCLUDE)}"\..\io\iocontrl.ipp"\
	{$(INCLUDE)}"\..\io\iostatus.h"\
	{$(INCLUDE)}"\..\io\iostatus.ipp"\
	{$(INCLUDE)}"\..\io\openctrl.h"\
	{$(INCLUDE)}"\..\io\openctrl.ipp"\
	{$(INCLUDE)}"\..\io\sid.h"\
	{$(INCLUDE)}"\..\io\types.h"\
	{$(INCLUDE)}"\..\io\utility.h"\
	{$(INCLUDE)}"\..\std\iosfwd"\
	{$(INCLUDE)}"\..\std\iostream"\
	{$(INCLUDE)}"\..\std\istream"\
	{$(INCLUDE)}"\..\std\ostream"\
	{$(INCLUDE)}"\..\std\sstream"\
	{$(INCLUDE)}"\..\std\string"\
	{$(INCLUDE)}"\..\stl\allocate.cc"\
	{$(INCLUDE)}"\..\stl\allocate.h"\
	{$(INCLUDE)}"\..\stl\allocimp.h"\
	{$(INCLUDE)}"\..\stl\common.h"\
	{$(INCLUDE)}"\..\stl\config.h"\
	{$(INCLUDE)}"\..\stl\iterator.cc"\
	{$(INCLUDE)}"\..\stl\iterator.h"\
	{$(INCLUDE)}"\..\stl\ops.h"\
	{$(INCLUDE)}"\..\stl\pair.h"\
	{$(INCLUDE)}"\..\stl\stlerror.h"\
	{$(INCLUDE)}"\..\string\basic.cc"\
	{$(INCLUDE)}"\..\string\basic.h"\
	{$(INCLUDE)}"\..\string\basic.ipp"\
	{$(INCLUDE)}"\..\string\config.h"\
	{$(INCLUDE)}"\..\string\search.cc"\
	{$(INCLUDE)}"\..\string\search.h"\
	{$(INCLUDE)}"\..\string\string.h"\
	{$(INCLUDE)}"\..\string\traits.cc"\
	{$(INCLUDE)}"\..\string\traits.h"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\..\utility\memory.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\extern.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
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
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\file.obj" : $(SOURCE) $(DEP_CPP_FILE_) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\file.obj" : $(SOURCE) $(DEP_CPP_FILE_) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\file.obj" : $(SOURCE) $(DEP_CPP_FILE_) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\file\src\filedev.cpp
DEP_CPP_FILED=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\except\file.h"\
	{$(INCLUDE)}"\..\except\file.ipp"\
	{$(INCLUDE)}"\..\except\io.h"\
	{$(INCLUDE)}"\..\except\io.ipp"\
	{$(INCLUDE)}"\..\except\throw.h"\
	{$(INCLUDE)}"\..\except\toolkit.h"\
	{$(INCLUDE)}"\..\except\toolkit.ipp"\
	{$(INCLUDE)}"\..\file\file.h"\
	{$(INCLUDE)}"\..\file\file.ipp"\
	{$(INCLUDE)}"\..\file\filedev.h"\
	{$(INCLUDE)}"\..\file\filedev.ipp"\
	{$(INCLUDE)}"\..\file\filelock.h"\
	{$(INCLUDE)}"\..\file\filelock.ipp"\
	{$(INCLUDE)}"\..\internal\call.h"\
	{$(INCLUDE)}"\..\internal\errno.h"\
	{$(INCLUDE)}"\..\internal\error.h"\
	{$(INCLUDE)}"\..\internal\fmacros.h"\
	{$(INCLUDE)}"\..\internal\syscall.h"\
	{$(INCLUDE)}"\..\io.h"\
	{$(INCLUDE)}"\..\io\_startup.h"\
	{$(INCLUDE)}"\..\io\adapter.h"\
	{$(INCLUDE)}"\..\io\adapter.ipp"\
	{$(INCLUDE)}"\..\io\bufdev.h"\
	{$(INCLUDE)}"\..\io\bufdev.ipp"\
	{$(INCLUDE)}"\..\io\buffer.h"\
	{$(INCLUDE)}"\..\io\buffer.ipp"\
	{$(INCLUDE)}"\..\io\cache.h"\
	{$(INCLUDE)}"\..\io\cache.ipp"\
	{$(INCLUDE)}"\..\io\device.h"\
	{$(INCLUDE)}"\..\io\device.ipp"\
	{$(INCLUDE)}"\..\io\iocontrl.h"\
	{$(INCLUDE)}"\..\io\iocontrl.ipp"\
	{$(INCLUDE)}"\..\io\iostatus.h"\
	{$(INCLUDE)}"\..\io\iostatus.ipp"\
	{$(INCLUDE)}"\..\io\openctrl.h"\
	{$(INCLUDE)}"\..\io\openctrl.ipp"\
	{$(INCLUDE)}"\..\io\sid.h"\
	{$(INCLUDE)}"\..\io\types.h"\
	{$(INCLUDE)}"\..\io\utility.h"\
	{$(INCLUDE)}"\..\std\iosfwd"\
	{$(INCLUDE)}"\..\std\iostream"\
	{$(INCLUDE)}"\..\std\istream"\
	{$(INCLUDE)}"\..\std\ostream"\
	{$(INCLUDE)}"\..\std\sstream"\
	{$(INCLUDE)}"\..\std\string"\
	{$(INCLUDE)}"\..\stl\allocate.cc"\
	{$(INCLUDE)}"\..\stl\allocate.h"\
	{$(INCLUDE)}"\..\stl\allocimp.h"\
	{$(INCLUDE)}"\..\stl\common.h"\
	{$(INCLUDE)}"\..\stl\config.h"\
	{$(INCLUDE)}"\..\stl\iterator.cc"\
	{$(INCLUDE)}"\..\stl\iterator.h"\
	{$(INCLUDE)}"\..\stl\ops.h"\
	{$(INCLUDE)}"\..\stl\pair.h"\
	{$(INCLUDE)}"\..\stl\stlerror.h"\
	{$(INCLUDE)}"\..\string\basic.cc"\
	{$(INCLUDE)}"\..\string\basic.h"\
	{$(INCLUDE)}"\..\string\basic.ipp"\
	{$(INCLUDE)}"\..\string\config.h"\
	{$(INCLUDE)}"\..\string\search.cc"\
	{$(INCLUDE)}"\..\string\search.h"\
	{$(INCLUDE)}"\..\string\string.h"\
	{$(INCLUDE)}"\..\string\traits.cc"\
	{$(INCLUDE)}"\..\string\traits.h"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\..\utility\memory.h"\
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
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
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
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\filedev.obj" : $(SOURCE) $(DEP_CPP_FILED) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\filedev.obj" : $(SOURCE) $(DEP_CPP_FILED) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\filedev.obj" : $(SOURCE) $(DEP_CPP_FILED) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\file\src\fileinit.cpp
DEP_CPP_FILEI=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\file\_startup.h"\
	{$(INCLUDE)}"\..\io\_startup.h"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\fileinit.obj" : $(SOURCE) $(DEP_CPP_FILEI) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\fileinit.obj" : $(SOURCE) $(DEP_CPP_FILEI) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\fileinit.obj" : $(SOURCE) $(DEP_CPP_FILEI) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\file\src\filelock.cpp
DEP_CPP_FILEL=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\except\file.h"\
	{$(INCLUDE)}"\..\except\file.ipp"\
	{$(INCLUDE)}"\..\except\io.h"\
	{$(INCLUDE)}"\..\except\io.ipp"\
	{$(INCLUDE)}"\..\except\throw.h"\
	{$(INCLUDE)}"\..\except\toolkit.h"\
	{$(INCLUDE)}"\..\except\toolkit.ipp"\
	{$(INCLUDE)}"\..\file\file.h"\
	{$(INCLUDE)}"\..\file\file.ipp"\
	{$(INCLUDE)}"\..\file\filelock.h"\
	{$(INCLUDE)}"\..\file\filelock.ipp"\
	{$(INCLUDE)}"\..\internal\call.h"\
	{$(INCLUDE)}"\..\internal\errno.h"\
	{$(INCLUDE)}"\..\internal\error.h"\
	{$(INCLUDE)}"\..\internal\fmacros.h"\
	{$(INCLUDE)}"\..\internal\syscall.h"\
	{$(INCLUDE)}"\..\io.h"\
	{$(INCLUDE)}"\..\io\_startup.h"\
	{$(INCLUDE)}"\..\io\adapter.h"\
	{$(INCLUDE)}"\..\io\adapter.ipp"\
	{$(INCLUDE)}"\..\io\bufdev.h"\
	{$(INCLUDE)}"\..\io\bufdev.ipp"\
	{$(INCLUDE)}"\..\io\buffer.h"\
	{$(INCLUDE)}"\..\io\buffer.ipp"\
	{$(INCLUDE)}"\..\io\cache.h"\
	{$(INCLUDE)}"\..\io\cache.ipp"\
	{$(INCLUDE)}"\..\io\device.h"\
	{$(INCLUDE)}"\..\io\device.ipp"\
	{$(INCLUDE)}"\..\io\iocontrl.h"\
	{$(INCLUDE)}"\..\io\iocontrl.ipp"\
	{$(INCLUDE)}"\..\io\iostatus.h"\
	{$(INCLUDE)}"\..\io\iostatus.ipp"\
	{$(INCLUDE)}"\..\io\openctrl.h"\
	{$(INCLUDE)}"\..\io\openctrl.ipp"\
	{$(INCLUDE)}"\..\io\sid.h"\
	{$(INCLUDE)}"\..\io\types.h"\
	{$(INCLUDE)}"\..\io\utility.h"\
	{$(INCLUDE)}"\..\std\iosfwd"\
	{$(INCLUDE)}"\..\std\iostream"\
	{$(INCLUDE)}"\..\std\istream"\
	{$(INCLUDE)}"\..\std\ostream"\
	{$(INCLUDE)}"\..\std\sstream"\
	{$(INCLUDE)}"\..\std\string"\
	{$(INCLUDE)}"\..\stl\allocate.cc"\
	{$(INCLUDE)}"\..\stl\allocate.h"\
	{$(INCLUDE)}"\..\stl\allocimp.h"\
	{$(INCLUDE)}"\..\stl\common.h"\
	{$(INCLUDE)}"\..\stl\config.h"\
	{$(INCLUDE)}"\..\stl\iterator.cc"\
	{$(INCLUDE)}"\..\stl\iterator.h"\
	{$(INCLUDE)}"\..\stl\ops.h"\
	{$(INCLUDE)}"\..\stl\pair.h"\
	{$(INCLUDE)}"\..\stl\stlerror.h"\
	{$(INCLUDE)}"\..\string\basic.cc"\
	{$(INCLUDE)}"\..\string\basic.h"\
	{$(INCLUDE)}"\..\string\basic.ipp"\
	{$(INCLUDE)}"\..\string\config.h"\
	{$(INCLUDE)}"\..\string\search.cc"\
	{$(INCLUDE)}"\..\string\search.h"\
	{$(INCLUDE)}"\..\string\string.h"\
	{$(INCLUDE)}"\..\string\traits.cc"\
	{$(INCLUDE)}"\..\string\traits.h"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\..\utility\memory.h"\
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
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
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
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\filelock.obj" : $(SOURCE) $(DEP_CPP_FILEL) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\filelock.obj" : $(SOURCE) $(DEP_CPP_FILEL) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\filelock.obj" : $(SOURCE) $(DEP_CPP_FILEL) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\file\src\filesys.cpp
DEP_CPP_FILES=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\except\file.h"\
	{$(INCLUDE)}"\..\except\file.ipp"\
	{$(INCLUDE)}"\..\except\io.h"\
	{$(INCLUDE)}"\..\except\io.ipp"\
	{$(INCLUDE)}"\..\except\throw.h"\
	{$(INCLUDE)}"\..\except\toolkit.h"\
	{$(INCLUDE)}"\..\except\toolkit.ipp"\
	{$(INCLUDE)}"\..\file\file.h"\
	{$(INCLUDE)}"\..\file\file.ipp"\
	{$(INCLUDE)}"\..\file\filelock.h"\
	{$(INCLUDE)}"\..\file\filelock.ipp"\
	{$(INCLUDE)}"\..\file\filesys.h"\
	{$(INCLUDE)}"\..\file\filesys.ipp"\
	{$(INCLUDE)}"\..\internal\call.h"\
	{$(INCLUDE)}"\..\internal\errno.h"\
	{$(INCLUDE)}"\..\internal\error.h"\
	{$(INCLUDE)}"\..\internal\fmacros.h"\
	{$(INCLUDE)}"\..\internal\syscall.h"\
	{$(INCLUDE)}"\..\io.h"\
	{$(INCLUDE)}"\..\io\_startup.h"\
	{$(INCLUDE)}"\..\io\adapter.h"\
	{$(INCLUDE)}"\..\io\adapter.ipp"\
	{$(INCLUDE)}"\..\io\bufdev.h"\
	{$(INCLUDE)}"\..\io\bufdev.ipp"\
	{$(INCLUDE)}"\..\io\buffer.h"\
	{$(INCLUDE)}"\..\io\buffer.ipp"\
	{$(INCLUDE)}"\..\io\cache.h"\
	{$(INCLUDE)}"\..\io\cache.ipp"\
	{$(INCLUDE)}"\..\io\device.h"\
	{$(INCLUDE)}"\..\io\device.ipp"\
	{$(INCLUDE)}"\..\io\iocontrl.h"\
	{$(INCLUDE)}"\..\io\iocontrl.ipp"\
	{$(INCLUDE)}"\..\io\iostatus.h"\
	{$(INCLUDE)}"\..\io\iostatus.ipp"\
	{$(INCLUDE)}"\..\io\openctrl.h"\
	{$(INCLUDE)}"\..\io\openctrl.ipp"\
	{$(INCLUDE)}"\..\io\sid.h"\
	{$(INCLUDE)}"\..\io\types.h"\
	{$(INCLUDE)}"\..\io\utility.h"\
	{$(INCLUDE)}"\..\std\iosfwd"\
	{$(INCLUDE)}"\..\std\iostream"\
	{$(INCLUDE)}"\..\std\istream"\
	{$(INCLUDE)}"\..\std\ostream"\
	{$(INCLUDE)}"\..\std\sstream"\
	{$(INCLUDE)}"\..\std\string"\
	{$(INCLUDE)}"\..\stl\allocate.cc"\
	{$(INCLUDE)}"\..\stl\allocate.h"\
	{$(INCLUDE)}"\..\stl\allocimp.h"\
	{$(INCLUDE)}"\..\stl\common.h"\
	{$(INCLUDE)}"\..\stl\config.h"\
	{$(INCLUDE)}"\..\stl\iterator.cc"\
	{$(INCLUDE)}"\..\stl\iterator.h"\
	{$(INCLUDE)}"\..\stl\ops.h"\
	{$(INCLUDE)}"\..\stl\pair.h"\
	{$(INCLUDE)}"\..\stl\stlerror.h"\
	{$(INCLUDE)}"\..\string\basic.cc"\
	{$(INCLUDE)}"\..\string\basic.h"\
	{$(INCLUDE)}"\..\string\basic.ipp"\
	{$(INCLUDE)}"\..\string\config.h"\
	{$(INCLUDE)}"\..\string\search.cc"\
	{$(INCLUDE)}"\..\string\search.h"\
	{$(INCLUDE)}"\..\string\string.h"\
	{$(INCLUDE)}"\..\string\traits.cc"\
	{$(INCLUDE)}"\..\string\traits.h"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\..\utility\memory.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\extern.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
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
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\filesys.obj" : $(SOURCE) $(DEP_CPP_FILES) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\filesys.obj" : $(SOURCE) $(DEP_CPP_FILES) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\filesys.obj" : $(SOURCE) $(DEP_CPP_FILES) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\file\src\dir.cpp

!IF  "$(CFG)" == "standards - Win32 MT Debug"

DEP_CPP_DIR_C=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\except\config.h"\
	{$(INCLUDE)}"\..\except\except.h"\
	{$(INCLUDE)}"\..\except\file.h"\
	{$(INCLUDE)}"\..\except\file.ipp"\
	{$(INCLUDE)}"\..\except\stdex.h"\
	{$(INCLUDE)}"\..\except\throw.h"\
	{$(INCLUDE)}"\..\except\toolkit.h"\
	{$(INCLUDE)}"\..\except\toolkit.ipp"\
	{$(INCLUDE)}"\..\extern.h"\
	{$(INCLUDE)}"\..\file\dir.h"\
	{$(INCLUDE)}"\..\file\dir.ipp"\
	{$(INCLUDE)}"\..\file\path.h"\
	{$(INCLUDE)}"\..\file\path.ipp"\
	{$(INCLUDE)}"\..\internal\call.h"\
	{$(INCLUDE)}"\..\internal\errno.h"\
	{$(INCLUDE)}"\..\internal\error.h"\
	{$(INCLUDE)}"\..\internal\fmacros.h"\
	{$(INCLUDE)}"\..\internal\syscall.h"\
	{$(INCLUDE)}"\..\io\iostatus.h"\
	{$(INCLUDE)}"\..\io\iostatus.ipp"\
	{$(INCLUDE)}"\..\io\openctrl.h"\
	{$(INCLUDE)}"\..\io\openctrl.ipp"\
	{$(INCLUDE)}"\..\io\sid.h"\
	{$(INCLUDE)}"\..\io\types.h"\
	{$(INCLUDE)}"\..\io\utility.h"\
	{$(INCLUDE)}"\..\std\algorithm"\
	{$(INCLUDE)}"\..\std\iosfwd"\
	{$(INCLUDE)}"\..\std\iostream"\
	{$(INCLUDE)}"\..\std\istream"\
	{$(INCLUDE)}"\..\std\ostream"\
	{$(INCLUDE)}"\..\std\sstream"\
	{$(INCLUDE)}"\..\std\string"\
	{$(INCLUDE)}"\..\std\vector"\
	{$(INCLUDE)}"\..\stl\advalgo.cc"\
	{$(INCLUDE)}"\..\stl\advalgo.h"\
	{$(INCLUDE)}"\..\stl\allocate.cc"\
	{$(INCLUDE)}"\..\stl\allocate.h"\
	{$(INCLUDE)}"\..\stl\allocimp.h"\
	{$(INCLUDE)}"\..\stl\auxalgo.cc"\
	{$(INCLUDE)}"\..\stl\auxalgo.h"\
	{$(INCLUDE)}"\..\stl\basalgo.cc"\
	{$(INCLUDE)}"\..\stl\basalgo.h"\
	{$(INCLUDE)}"\..\stl\common.h"\
	{$(INCLUDE)}"\..\stl\config.h"\
	{$(INCLUDE)}"\..\stl\function.h"\
	{$(INCLUDE)}"\..\stl\heap.cc"\
	{$(INCLUDE)}"\..\stl\heap.h"\
	{$(INCLUDE)}"\..\stl\helper.cc"\
	{$(INCLUDE)}"\..\stl\helper.h"\
	{$(INCLUDE)}"\..\stl\iterator.cc"\
	{$(INCLUDE)}"\..\stl\iterator.h"\
	{$(INCLUDE)}"\..\stl\ops.h"\
	{$(INCLUDE)}"\..\stl\pair.h"\
	{$(INCLUDE)}"\..\stl\randgen.h"\
	{$(INCLUDE)}"\..\stl\rawalgo.cc"\
	{$(INCLUDE)}"\..\stl\rawalgo.h"\
	{$(INCLUDE)}"\..\stl\rawiter.h"\
	{$(INCLUDE)}"\..\stl\sort.cc"\
	{$(INCLUDE)}"\..\stl\sort.h"\
	{$(INCLUDE)}"\..\stl\stlerror.h"\
	{$(INCLUDE)}"\..\stl\tempbuf.cc"\
	{$(INCLUDE)}"\..\stl\tempbuf.h"\
	{$(INCLUDE)}"\..\stl\vector.cc"\
	{$(INCLUDE)}"\..\stl\vector.h"\
	{$(INCLUDE)}"\..\string\basic.cc"\
	{$(INCLUDE)}"\..\string\basic.h"\
	{$(INCLUDE)}"\..\string\basic.ipp"\
	{$(INCLUDE)}"\..\string\config.h"\
	{$(INCLUDE)}"\..\string\search.cc"\
	{$(INCLUDE)}"\..\string\search.h"\
	{$(INCLUDE)}"\..\string\string.h"\
	{$(INCLUDE)}"\..\string\traits.cc"\
	{$(INCLUDE)}"\..\string\traits.h"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\..\utility\memory.h"\
	{$(INCLUDE)}"\ALGORITHM"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\extern.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
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
	

"$(INTDIR)\dir.obj" : $(SOURCE) $(DEP_CPP_DIR_C) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"

DEP_CPP_DIR_C=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\except\config.h"\
	{$(INCLUDE)}"\..\except\except.h"\
	{$(INCLUDE)}"\..\except\file.h"\
	{$(INCLUDE)}"\..\except\file.ipp"\
	{$(INCLUDE)}"\..\except\stdex.h"\
	{$(INCLUDE)}"\..\except\throw.h"\
	{$(INCLUDE)}"\..\except\toolkit.h"\
	{$(INCLUDE)}"\..\except\toolkit.ipp"\
	{$(INCLUDE)}"\..\extern.h"\
	{$(INCLUDE)}"\..\file\dir.h"\
	{$(INCLUDE)}"\..\file\dir.ipp"\
	{$(INCLUDE)}"\..\file\path.h"\
	{$(INCLUDE)}"\..\file\path.ipp"\
	{$(INCLUDE)}"\..\internal\call.h"\
	{$(INCLUDE)}"\..\internal\errno.h"\
	{$(INCLUDE)}"\..\internal\error.h"\
	{$(INCLUDE)}"\..\internal\fmacros.h"\
	{$(INCLUDE)}"\..\internal\syscall.h"\
	{$(INCLUDE)}"\..\io\iostatus.h"\
	{$(INCLUDE)}"\..\io\iostatus.ipp"\
	{$(INCLUDE)}"\..\io\openctrl.h"\
	{$(INCLUDE)}"\..\io\openctrl.ipp"\
	{$(INCLUDE)}"\..\io\sid.h"\
	{$(INCLUDE)}"\..\io\types.h"\
	{$(INCLUDE)}"\..\io\utility.h"\
	{$(INCLUDE)}"\..\std\algorithm"\
	{$(INCLUDE)}"\..\std\iosfwd"\
	{$(INCLUDE)}"\..\std\iostream"\
	{$(INCLUDE)}"\..\std\istream"\
	{$(INCLUDE)}"\..\std\ostream"\
	{$(INCLUDE)}"\..\std\sstream"\
	{$(INCLUDE)}"\..\std\string"\
	{$(INCLUDE)}"\..\std\vector"\
	{$(INCLUDE)}"\..\stl\allocate.cc"\
	{$(INCLUDE)}"\..\stl\allocate.h"\
	{$(INCLUDE)}"\..\stl\allocimp.h"\
	{$(INCLUDE)}"\..\stl\basalgo.cc"\
	{$(INCLUDE)}"\..\stl\basalgo.h"\
	{$(INCLUDE)}"\..\stl\common.h"\
	{$(INCLUDE)}"\..\stl\config.h"\
	{$(INCLUDE)}"\..\stl\helper.cc"\
	{$(INCLUDE)}"\..\stl\helper.h"\
	{$(INCLUDE)}"\..\stl\iterator.cc"\
	{$(INCLUDE)}"\..\stl\iterator.h"\
	{$(INCLUDE)}"\..\stl\ops.h"\
	{$(INCLUDE)}"\..\stl\pair.h"\
	{$(INCLUDE)}"\..\stl\rawalgo.cc"\
	{$(INCLUDE)}"\..\stl\rawalgo.h"\
	{$(INCLUDE)}"\..\stl\stlerror.h"\
	{$(INCLUDE)}"\..\stl\vector.cc"\
	{$(INCLUDE)}"\..\stl\vector.h"\
	{$(INCLUDE)}"\..\string\basic.cc"\
	{$(INCLUDE)}"\..\string\basic.h"\
	{$(INCLUDE)}"\..\string\basic.ipp"\
	{$(INCLUDE)}"\..\string\config.h"\
	{$(INCLUDE)}"\..\string\search.cc"\
	{$(INCLUDE)}"\..\string\search.h"\
	{$(INCLUDE)}"\..\string\string.h"\
	{$(INCLUDE)}"\..\string\traits.cc"\
	{$(INCLUDE)}"\..\string\traits.h"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\..\utility\memory.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\extern.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
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
	

"$(INTDIR)\dir.obj" : $(SOURCE) $(DEP_CPP_DIR_C) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"

DEP_CPP_DIR_C=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\except\config.h"\
	{$(INCLUDE)}"\..\except\except.h"\
	{$(INCLUDE)}"\..\except\file.h"\
	{$(INCLUDE)}"\..\except\file.ipp"\
	{$(INCLUDE)}"\..\except\stdex.h"\
	{$(INCLUDE)}"\..\except\throw.h"\
	{$(INCLUDE)}"\..\except\toolkit.h"\
	{$(INCLUDE)}"\..\except\toolkit.ipp"\
	{$(INCLUDE)}"\..\extern.h"\
	{$(INCLUDE)}"\..\file\dir.h"\
	{$(INCLUDE)}"\..\file\dir.ipp"\
	{$(INCLUDE)}"\..\file\path.h"\
	{$(INCLUDE)}"\..\file\path.ipp"\
	{$(INCLUDE)}"\..\internal\call.h"\
	{$(INCLUDE)}"\..\internal\errno.h"\
	{$(INCLUDE)}"\..\internal\error.h"\
	{$(INCLUDE)}"\..\internal\fmacros.h"\
	{$(INCLUDE)}"\..\internal\syscall.h"\
	{$(INCLUDE)}"\..\io\iostatus.h"\
	{$(INCLUDE)}"\..\io\iostatus.ipp"\
	{$(INCLUDE)}"\..\io\openctrl.h"\
	{$(INCLUDE)}"\..\io\openctrl.ipp"\
	{$(INCLUDE)}"\..\io\sid.h"\
	{$(INCLUDE)}"\..\io\types.h"\
	{$(INCLUDE)}"\..\io\utility.h"\
	{$(INCLUDE)}"\..\std\algorithm"\
	{$(INCLUDE)}"\..\std\iosfwd"\
	{$(INCLUDE)}"\..\std\iostream"\
	{$(INCLUDE)}"\..\std\istream"\
	{$(INCLUDE)}"\..\std\ostream"\
	{$(INCLUDE)}"\..\std\sstream"\
	{$(INCLUDE)}"\..\std\string"\
	{$(INCLUDE)}"\..\std\vector"\
	{$(INCLUDE)}"\..\stl\advalgo.cc"\
	{$(INCLUDE)}"\..\stl\advalgo.h"\
	{$(INCLUDE)}"\..\stl\allocate.cc"\
	{$(INCLUDE)}"\..\stl\allocate.h"\
	{$(INCLUDE)}"\..\stl\allocimp.h"\
	{$(INCLUDE)}"\..\stl\auxalgo.cc"\
	{$(INCLUDE)}"\..\stl\auxalgo.h"\
	{$(INCLUDE)}"\..\stl\basalgo.cc"\
	{$(INCLUDE)}"\..\stl\basalgo.h"\
	{$(INCLUDE)}"\..\stl\common.h"\
	{$(INCLUDE)}"\..\stl\config.h"\
	{$(INCLUDE)}"\..\stl\function.h"\
	{$(INCLUDE)}"\..\stl\heap.cc"\
	{$(INCLUDE)}"\..\stl\heap.h"\
	{$(INCLUDE)}"\..\stl\helper.cc"\
	{$(INCLUDE)}"\..\stl\helper.h"\
	{$(INCLUDE)}"\..\stl\iterator.cc"\
	{$(INCLUDE)}"\..\stl\iterator.h"\
	{$(INCLUDE)}"\..\stl\ops.h"\
	{$(INCLUDE)}"\..\stl\pair.h"\
	{$(INCLUDE)}"\..\stl\randgen.h"\
	{$(INCLUDE)}"\..\stl\rawalgo.cc"\
	{$(INCLUDE)}"\..\stl\rawalgo.h"\
	{$(INCLUDE)}"\..\stl\rawiter.h"\
	{$(INCLUDE)}"\..\stl\sort.cc"\
	{$(INCLUDE)}"\..\stl\sort.h"\
	{$(INCLUDE)}"\..\stl\stlerror.h"\
	{$(INCLUDE)}"\..\stl\tempbuf.cc"\
	{$(INCLUDE)}"\..\stl\tempbuf.h"\
	{$(INCLUDE)}"\..\stl\vector.cc"\
	{$(INCLUDE)}"\..\stl\vector.h"\
	{$(INCLUDE)}"\..\string\basic.cc"\
	{$(INCLUDE)}"\..\string\basic.h"\
	{$(INCLUDE)}"\..\string\basic.ipp"\
	{$(INCLUDE)}"\..\string\config.h"\
	{$(INCLUDE)}"\..\string\search.cc"\
	{$(INCLUDE)}"\..\string\search.h"\
	{$(INCLUDE)}"\..\string\string.h"\
	{$(INCLUDE)}"\..\string\traits.cc"\
	{$(INCLUDE)}"\..\string\traits.h"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\..\utility\memory.h"\
	{$(INCLUDE)}"\ALGORITHM"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\extern.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
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
	

"$(INTDIR)\dir.obj" : $(SOURCE) $(DEP_CPP_DIR_C) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\except\src\file_ex.cpp
DEP_CPP_FILE_E=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\except\file.h"\
	{$(INCLUDE)}"\..\except\file.ipp"\
	{$(INCLUDE)}"\..\except\toolkit.h"\
	{$(INCLUDE)}"\..\except\toolkit.ipp"\
	{$(INCLUDE)}"\..\std\iostream"\
	{$(INCLUDE)}"\..\type\prim.h"\
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
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
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
	

!IF  "$(CFG)" == "standards - Win32 MT Debug"


"$(INTDIR)\file_ex.obj" : $(SOURCE) $(DEP_CPP_FILE_E) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"


"$(INTDIR)\file_ex.obj" : $(SOURCE) $(DEP_CPP_FILE_E) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"


"$(INTDIR)\file_ex.obj" : $(SOURCE) $(DEP_CPP_FILE_E) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
# End Target
################################################################################
# Begin Target

# Name "standards uss - Win32 Release"
# Name "standards uss - Win32 Debug"

!IF  "$(CFG)" == "standards uss - Win32 Release"

!ELSEIF  "$(CFG)" == "standards uss - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\uss\std\src\std_uss.cpp

!IF  "$(CFG)" == "standards uss - Win32 Release"

DEP_CPP_STD_U=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\header.h"\
	{$(INCLUDE)}"\..\internal\fmacros.h"\
	{$(INCLUDE)}"\..\io\adapter.h"\
	{$(INCLUDE)}"\..\io\adapter.ipp"\
	{$(INCLUDE)}"\..\rtti\cast.h"\
	{$(INCLUDE)}"\..\rtti\cast.ipp"\
	{$(INCLUDE)}"\..\rtti\class.h"\
	{$(INCLUDE)}"\..\rtti\class.ipp"\
	{$(INCLUDE)}"\..\rtti\hmacros.h"\
	{$(INCLUDE)}"\..\rtti\hmacros1.h"\
	{$(INCLUDE)}"\..\rtti\hmacros3.h"\
	{$(INCLUDE)}"\..\rtti\regmacro.h"\
	{$(INCLUDE)}"\..\rtti\rtti.h"\
	{$(INCLUDE)}"\..\rtti\smacros.h"\
	{$(INCLUDE)}"\..\std\iosfwd"\
	{$(INCLUDE)}"\..\std\istream"\
	{$(INCLUDE)}"\..\std\ostream"\
	{$(INCLUDE)}"\..\std\string"\
	{$(INCLUDE)}"\..\std\typeinfo"\
	{$(INCLUDE)}"\..\stl\allocate.cc"\
	{$(INCLUDE)}"\..\stl\allocate.h"\
	{$(INCLUDE)}"\..\stl\allocimp.h"\
	{$(INCLUDE)}"\..\stl\common.h"\
	{$(INCLUDE)}"\..\stl\config.h"\
	{$(INCLUDE)}"\..\stl\iterator.cc"\
	{$(INCLUDE)}"\..\stl\iterator.h"\
	{$(INCLUDE)}"\..\stl\ops.h"\
	{$(INCLUDE)}"\..\stl\pair.h"\
	{$(INCLUDE)}"\..\stl\stlerror.h"\
	{$(INCLUDE)}"\..\stream\bstream.h"\
	{$(INCLUDE)}"\..\stream\bstream.ipp"\
	{$(INCLUDE)}"\..\stream\hmacros.h"\
	{$(INCLUDE)}"\..\stream\protocol.h"\
	{$(INCLUDE)}"\..\stream\protocol.ipp"\
	{$(INCLUDE)}"\..\stream\rtti.h"\
	{$(INCLUDE)}"\..\stream\smacros.h"\
	{$(INCLUDE)}"\..\string\basic.cc"\
	{$(INCLUDE)}"\..\string\basic.h"\
	{$(INCLUDE)}"\..\string\basic.ipp"\
	{$(INCLUDE)}"\..\string\config.h"\
	{$(INCLUDE)}"\..\string\search.cc"\
	{$(INCLUDE)}"\..\string\search.h"\
	{$(INCLUDE)}"\..\string\string.h"\
	{$(INCLUDE)}"\..\string\traits.cc"\
	{$(INCLUDE)}"\..\string\traits.h"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\..\type\types.h"\
	{$(INCLUDE)}"\..\uss\id.h"\
	{$(INCLUDE)}"\..\uss\std\id.h"\
	{$(INCLUDE)}"\..\uss\std\string.h"\
	{$(INCLUDE)}"\..\utility\memory.h"\
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
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
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
	

"$(INTDIR)\std_uss.obj" : $(SOURCE) $(DEP_CPP_STD_U) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards uss - Win32 Debug"

DEP_CPP_STD_U=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\header.h"\
	{$(INCLUDE)}"\..\internal\fmacros.h"\
	{$(INCLUDE)}"\..\io\adapter.h"\
	{$(INCLUDE)}"\..\io\adapter.ipp"\
	{$(INCLUDE)}"\..\rtti\cast.h"\
	{$(INCLUDE)}"\..\rtti\cast.ipp"\
	{$(INCLUDE)}"\..\rtti\class.h"\
	{$(INCLUDE)}"\..\rtti\class.ipp"\
	{$(INCLUDE)}"\..\rtti\hmacros.h"\
	{$(INCLUDE)}"\..\rtti\hmacros1.h"\
	{$(INCLUDE)}"\..\rtti\hmacros3.h"\
	{$(INCLUDE)}"\..\rtti\regmacro.h"\
	{$(INCLUDE)}"\..\rtti\rtti.h"\
	{$(INCLUDE)}"\..\rtti\smacros.h"\
	{$(INCLUDE)}"\..\std\iosfwd"\
	{$(INCLUDE)}"\..\std\istream"\
	{$(INCLUDE)}"\..\std\ostream"\
	{$(INCLUDE)}"\..\std\string"\
	{$(INCLUDE)}"\..\std\typeinfo"\
	{$(INCLUDE)}"\..\stl\allocate.cc"\
	{$(INCLUDE)}"\..\stl\allocate.h"\
	{$(INCLUDE)}"\..\stl\allocimp.h"\
	{$(INCLUDE)}"\..\stl\common.h"\
	{$(INCLUDE)}"\..\stl\config.h"\
	{$(INCLUDE)}"\..\stl\iterator.cc"\
	{$(INCLUDE)}"\..\stl\iterator.h"\
	{$(INCLUDE)}"\..\stl\ops.h"\
	{$(INCLUDE)}"\..\stl\pair.h"\
	{$(INCLUDE)}"\..\stl\stlerror.h"\
	{$(INCLUDE)}"\..\stream\bstream.h"\
	{$(INCLUDE)}"\..\stream\bstream.ipp"\
	{$(INCLUDE)}"\..\stream\hmacros.h"\
	{$(INCLUDE)}"\..\stream\protocol.h"\
	{$(INCLUDE)}"\..\stream\protocol.ipp"\
	{$(INCLUDE)}"\..\stream\rtti.h"\
	{$(INCLUDE)}"\..\stream\smacros.h"\
	{$(INCLUDE)}"\..\string\basic.cc"\
	{$(INCLUDE)}"\..\string\basic.h"\
	{$(INCLUDE)}"\..\string\basic.ipp"\
	{$(INCLUDE)}"\..\string\config.h"\
	{$(INCLUDE)}"\..\string\search.cc"\
	{$(INCLUDE)}"\..\string\search.h"\
	{$(INCLUDE)}"\..\string\string.h"\
	{$(INCLUDE)}"\..\string\traits.cc"\
	{$(INCLUDE)}"\..\string\traits.h"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\..\type\types.h"\
	{$(INCLUDE)}"\..\uss\id.h"\
	{$(INCLUDE)}"\..\uss\std\id.h"\
	{$(INCLUDE)}"\..\uss\std\string.h"\
	{$(INCLUDE)}"\..\utility\memory.h"\
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
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
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
	

"$(INTDIR)\std_uss.obj" : $(SOURCE) $(DEP_CPP_STD_U) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\ToolKit\ospace\uss\file\src\file_uss.cpp

!IF  "$(CFG)" == "standards uss - Win32 Release"

DEP_CPP_FILE_U=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\file\filelock.h"\
	{$(INCLUDE)}"\..\file\filelock.ipp"\
	{$(INCLUDE)}"\..\file\path.h"\
	{$(INCLUDE)}"\..\file\path.ipp"\
	{$(INCLUDE)}"\..\header.h"\
	{$(INCLUDE)}"\..\internal\fmacros.h"\
	{$(INCLUDE)}"\..\io\adapter.h"\
	{$(INCLUDE)}"\..\io\adapter.ipp"\
	{$(INCLUDE)}"\..\io\sid.h"\
	{$(INCLUDE)}"\..\io\types.h"\
	{$(INCLUDE)}"\..\rtti\cast.h"\
	{$(INCLUDE)}"\..\rtti\cast.ipp"\
	{$(INCLUDE)}"\..\rtti\class.h"\
	{$(INCLUDE)}"\..\rtti\class.ipp"\
	{$(INCLUDE)}"\..\rtti\hmacros.h"\
	{$(INCLUDE)}"\..\rtti\hmacros1.h"\
	{$(INCLUDE)}"\..\rtti\hmacros3.h"\
	{$(INCLUDE)}"\..\rtti\regmacro.h"\
	{$(INCLUDE)}"\..\rtti\rtti.h"\
	{$(INCLUDE)}"\..\rtti\smacros.h"\
	{$(INCLUDE)}"\..\std\iosfwd"\
	{$(INCLUDE)}"\..\std\iostream"\
	{$(INCLUDE)}"\..\std\istream"\
	{$(INCLUDE)}"\..\std\ostream"\
	{$(INCLUDE)}"\..\std\string"\
	{$(INCLUDE)}"\..\std\typeinfo"\
	{$(INCLUDE)}"\..\stl\allocate.cc"\
	{$(INCLUDE)}"\..\stl\allocate.h"\
	{$(INCLUDE)}"\..\stl\allocimp.h"\
	{$(INCLUDE)}"\..\stl\common.h"\
	{$(INCLUDE)}"\..\stl\config.h"\
	{$(INCLUDE)}"\..\stl\iterator.cc"\
	{$(INCLUDE)}"\..\stl\iterator.h"\
	{$(INCLUDE)}"\..\stl\ops.h"\
	{$(INCLUDE)}"\..\stl\pair.h"\
	{$(INCLUDE)}"\..\stl\stlerror.h"\
	{$(INCLUDE)}"\..\stream\bstream.h"\
	{$(INCLUDE)}"\..\stream\bstream.ipp"\
	{$(INCLUDE)}"\..\stream\hmacros.h"\
	{$(INCLUDE)}"\..\stream\protocol.h"\
	{$(INCLUDE)}"\..\stream\protocol.ipp"\
	{$(INCLUDE)}"\..\stream\rtti.h"\
	{$(INCLUDE)}"\..\stream\smacros.h"\
	{$(INCLUDE)}"\..\string\basic.cc"\
	{$(INCLUDE)}"\..\string\basic.h"\
	{$(INCLUDE)}"\..\string\basic.ipp"\
	{$(INCLUDE)}"\..\string\config.h"\
	{$(INCLUDE)}"\..\string\search.cc"\
	{$(INCLUDE)}"\..\string\search.h"\
	{$(INCLUDE)}"\..\string\string.h"\
	{$(INCLUDE)}"\..\string\traits.cc"\
	{$(INCLUDE)}"\..\string\traits.h"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\..\type\types.h"\
	{$(INCLUDE)}"\..\uss\file\filelock.h"\
	{$(INCLUDE)}"\..\uss\file\id.h"\
	{$(INCLUDE)}"\..\uss\file\path.h"\
	{$(INCLUDE)}"\..\uss\id.h"\
	{$(INCLUDE)}"\..\uss\std\string.h"\
	{$(INCLUDE)}"\..\utility\memory.h"\
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
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\sys\TYPES.H"\
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
	

"$(INTDIR)\file_uss.obj" : $(SOURCE) $(DEP_CPP_FILE_U) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "standards uss - Win32 Debug"

DEP_CPP_FILE_U=\
	{$(INCLUDE)}"\..\config.h"\
	{$(INCLUDE)}"\..\file\filelock.h"\
	{$(INCLUDE)}"\..\file\filelock.ipp"\
	{$(INCLUDE)}"\..\file\path.h"\
	{$(INCLUDE)}"\..\file\path.ipp"\
	{$(INCLUDE)}"\..\header.h"\
	{$(INCLUDE)}"\..\internal\fmacros.h"\
	{$(INCLUDE)}"\..\io\adapter.h"\
	{$(INCLUDE)}"\..\io\adapter.ipp"\
	{$(INCLUDE)}"\..\io\sid.h"\
	{$(INCLUDE)}"\..\io\types.h"\
	{$(INCLUDE)}"\..\rtti\cast.h"\
	{$(INCLUDE)}"\..\rtti\cast.ipp"\
	{$(INCLUDE)}"\..\rtti\class.h"\
	{$(INCLUDE)}"\..\rtti\class.ipp"\
	{$(INCLUDE)}"\..\rtti\hmacros.h"\
	{$(INCLUDE)}"\..\rtti\hmacros1.h"\
	{$(INCLUDE)}"\..\rtti\hmacros3.h"\
	{$(INCLUDE)}"\..\rtti\regmacro.h"\
	{$(INCLUDE)}"\..\rtti\rtti.h"\
	{$(INCLUDE)}"\..\rtti\smacros.h"\
	{$(INCLUDE)}"\..\std\iosfwd"\
	{$(INCLUDE)}"\..\std\iostream"\
	{$(INCLUDE)}"\..\std\istream"\
	{$(INCLUDE)}"\..\std\ostream"\
	{$(INCLUDE)}"\..\std\string"\
	{$(INCLUDE)}"\..\std\typeinfo"\
	{$(INCLUDE)}"\..\stl\allocate.cc"\
	{$(INCLUDE)}"\..\stl\allocate.h"\
	{$(INCLUDE)}"\..\stl\allocimp.h"\
	{$(INCLUDE)}"\..\stl\common.h"\
	{$(INCLUDE)}"\..\stl\config.h"\
	{$(INCLUDE)}"\..\stl\iterator.cc"\
	{$(INCLUDE)}"\..\stl\iterator.h"\
	{$(INCLUDE)}"\..\stl\ops.h"\
	{$(INCLUDE)}"\..\stl\pair.h"\
	{$(INCLUDE)}"\..\stl\stlerror.h"\
	{$(INCLUDE)}"\..\stream\bstream.h"\
	{$(INCLUDE)}"\..\stream\bstream.ipp"\
	{$(INCLUDE)}"\..\stream\hmacros.h"\
	{$(INCLUDE)}"\..\stream\protocol.h"\
	{$(INCLUDE)}"\..\stream\protocol.ipp"\
	{$(INCLUDE)}"\..\stream\rtti.h"\
	{$(INCLUDE)}"\..\stream\smacros.h"\
	{$(INCLUDE)}"\..\string\basic.cc"\
	{$(INCLUDE)}"\..\string\basic.h"\
	{$(INCLUDE)}"\..\string\basic.ipp"\
	{$(INCLUDE)}"\..\string\config.h"\
	{$(INCLUDE)}"\..\string\search.cc"\
	{$(INCLUDE)}"\..\string\search.h"\
	{$(INCLUDE)}"\..\string\string.h"\
	{$(INCLUDE)}"\..\string\traits.cc"\
	{$(INCLUDE)}"\..\string\traits.h"\
	{$(INCLUDE)}"\..\type\prim.h"\
	{$(INCLUDE)}"\..\type\types.h"\
	{$(INCLUDE)}"\..\uss\file\filelock.h"\
	{$(INCLUDE)}"\..\uss\file\id.h"\
	{$(INCLUDE)}"\..\uss\file\path.h"\
	{$(INCLUDE)}"\..\uss\id.h"\
	{$(INCLUDE)}"\..\uss\std\string.h"\
	{$(INCLUDE)}"\..\utility\memory.h"\
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
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\sys\TYPES.H"\
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
	

"$(INTDIR)\file_uss.obj" : $(SOURCE) $(DEP_CPP_FILE_U) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
