# Microsoft Developer Studio Project File - Name="standards" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=standards - Win32 MT Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Ospace.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Ospace.mak" CFG="standards - Win32 MT Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "standards - Win32 MT Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "standards - Win32 MT Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "standards - Win32 MT Release Optimized" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "standards - Win32 MT Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\standard"
# PROP BASE Intermediate_Dir ".\standard"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /Gm /GR /GX /Zi /Od /I "\toolkit" /I "\toolkit\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "OS_WIN_95" /D "OS_BUILD_DLL" /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GR /GX /Zi /Od /FI"StdAfx.h" /D "_DEBUG" /D "OS_STL_ASSERT" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_WIN_95" /D "OS_BUILD_DLL" /D "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS" /D "WIN32" /D "_WINDOWS" /D "OS_BUILD_IO_TOOLKIT" /FR /Yu"StdAfx.h" /Fd".\Debug/Ospace5d.pdb" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"\toolkit\lib\std-2.0-vc4.0-mt-noalloc.dll"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:".\Debug\ospace5d.dll"
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying Target to Destination ...
TargetDir=.\Debug
TargetPath=.\Debug\ospace5d.dll
TargetName=ospace5d
InputPath=.\Debug\ospace5d.dll
SOURCE="$(InputPath)"

BuildCmds= \
	xcopy /F $(TargetPath) $(TRIASDIR_D) \
	xcopy /F $(TargetDir)\Ospace5d.pdb $(TRIASDIR_D) \
	xcopy /F $(TargetDir)\Ospace5d.lib $(TRIASLIB) \
	

"$(TRIASDIR_D)}$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASLIB)\Ospace5d.lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\standar0"
# PROP BASE Intermediate_Dir ".\standar0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /Gm /GR /GX /Zi /Od /I "\toolkit" /I "\toolkit\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "OS_WIN_95" /D "OS_BUILD_DLL" /YX /c
# ADD CPP /nologo /MD /W3 /GR /GX /ZI /Od /FI"StdAfx.h" /D "NDEBUG" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_WIN_95" /D "OS_BUILD_DLL" /D "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS" /D "WIN32" /D "_WINDOWS" /D "OS_BUILD_IO_TOOLKIT" /Yu"StdAfx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"\toolkit\lib\std-2.0-vc4.0-mt-noalloc.dll"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /debug /machine:I386 /implib:".\Release/Ospace5r.lib"
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying Target to Destination ...
TargetDir=.\Release
TargetPath=.\Release\Ospace.dll
TargetName=Ospace
InputPath=.\Release\Ospace.dll
SOURCE="$(InputPath)"

BuildCmds= \
	xcopy /F $(TargetPath) $(TRIASDIR_R) \
	xcopy /F $(TargetDir)\Ospace.pdb $(TRIASDIR_R) \
	xcopy /F $(TargetDir)\Ospace5r.lib $(TRIASLIB) \
	

"$(TRIASDIR_R)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASLIB)\Ospace5r.lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\standard"
# PROP BASE Intermediate_Dir ".\standard"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\RelOpt"
# PROP Intermediate_Dir ".\RelOpt"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GR /GX /Od /I "\toolkit" /I "\toolit\ospace" /D "OS_WIN_95" /D "OS_BUILD_DLL" /D "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS" /D "WIN32" /D "_WINDOWS" /D "OS_BUILD_IO_TOOLKIT" /D "OS_NO_WSTRING" /YX /c
# SUBTRACT BASE CPP /WX
# ADD CPP /nologo /MD /W3 /GR /GX /Zi /O2 /D "NDEBUG" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_WIN_95" /D "OS_BUILD_DLL" /D "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS" /D "WIN32" /D "_WINDOWS" /D "OS_BUILD_IO_TOOLKIT" /Yu"StdAfx.h" /FD /c
# SUBTRACT CPP /WX
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /debug /machine:I386
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "standards - Win32 MT Debug"
# Name "standards - Win32 MT Release"
# Name "standards - Win32 MT Release Optimized"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=..\io\src\adapter.cpp
# End Source File
# Begin Source File

SOURCE=..\stream\src\ascii.cpp
# End Source File
# Begin Source File

SOURCE=..\string\src\basic.cpp
# End Source File
# Begin Source File

SOURCE=..\stream\src\bstream.cpp
# End Source File
# Begin Source File

SOURCE=..\io\src\bufdev.cpp
# End Source File
# Begin Source File

SOURCE=..\io\src\buffer.cpp
# End Source File
# Begin Source File

SOURCE=..\io\src\cache.cpp
# End Source File
# Begin Source File

SOURCE=..\time\src\calendar.cpp
# End Source File
# Begin Source File

SOURCE=..\rtti\src\cast.cpp
# End Source File
# Begin Source File

SOURCE=..\rtti\src\class.cpp
# End Source File
# Begin Source File

SOURCE=..\rtti\src\classdb.cpp
# End Source File
# Begin Source File

SOURCE=..\sync\src\counting.cpp
# End Source File
# Begin Source File

SOURCE=..\sync\src\critical.cpp
# End Source File
# Begin Source File

SOURCE=..\time\src\date.cpp
# End Source File
# Begin Source File

SOURCE=..\io\src\device.cpp
# End Source File
# Begin Source File

SOURCE=..\file\src\dir.cpp
# End Source File
# Begin Source File

SOURCE=..\sync\src\eventsem.cpp
# End Source File
# Begin Source File

SOURCE=..\file\src\file.cpp
# End Source File
# Begin Source File

SOURCE=..\except\src\file_ex.cpp
# End Source File
# Begin Source File

SOURCE=..\file\src\filedev.cpp
# End Source File
# Begin Source File

SOURCE=..\file\src\fileinit.cpp
# End Source File
# Begin Source File

SOURCE=..\file\src\filelock.cpp
# End Source File
# Begin Source File

SOURCE=..\file\src\filesys.cpp
# End Source File
# Begin Source File

SOURCE=..\stream\src\fstrmdev.cpp
# End Source File
# Begin Source File

SOURCE=..\except\src\helper_ex.cpp
# End Source File
# Begin Source File

SOURCE=..\string\src\helpinit.cpp
# End Source File
# Begin Source File

SOURCE=..\except\src\io_ex.cpp
# End Source File
# Begin Source File

SOURCE=..\io\src\iocontrl.cpp
# End Source File
# Begin Source File

SOURCE=..\io\src\ioinit.cpp
# End Source File
# Begin Source File

SOURCE=..\COM\SRC\IOLESTRM.CPP
# End Source File
# Begin Source File

SOURCE=..\io\src\iostatus.cpp
# End Source File
# Begin Source File

SOURCE=..\stream\src\istrmdev.cpp
# End Source File
# Begin Source File

SOURCE=..\sync\src\mutex.cpp
# End Source File
# Begin Source File

SOURCE=..\stream\src\ndr.cpp
# End Source File
# Begin Source File

SOURCE=..\except\src\network_ex.cpp
# End Source File
# Begin Source File

SOURCE=..\COM\SRC\OLEBUF.CPP
# End Source File
# Begin Source File

SOURCE=..\COM\SRC\OLEBUF1.CPP
# End Source File
# Begin Source File

SOURCE=..\COM\SRC\OLESTREA.CPP
# End Source File
# Begin Source File

SOURCE=..\COM\SRC\OOLESTRM.CPP
# End Source File
# Begin Source File

SOURCE=..\io\src\openctrl.cpp
# End Source File
# Begin Source File

SOURCE=.\OSPAC50D.DEF

!IF  "$(CFG)" == "standards - Win32 MT Debug"

!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\OSPAC50R.DEF

!IF  "$(CFG)" == "standards - Win32 MT Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "standards - Win32 MT Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "standards - Win32 MT Release Optimized"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\dll\src\ospace.cpp
# End Source File
# Begin Source File

SOURCE=.\Ospace.rc
# End Source File
# Begin Source File

SOURCE=..\stream\src\ostrmdev.cpp
# End Source File
# Begin Source File

SOURCE=..\file\src\path.cpp
# End Source File
# Begin Source File

SOURCE=..\except\src\pipe_ex.cpp
# End Source File
# Begin Source File

SOURCE=..\stream\src\protocol.cpp
# End Source File
# Begin Source File

SOURCE=..\stl\src\randgen.cpp
# End Source File
# Begin Source File

SOURCE=..\string\src\regex.cpp
# End Source File
# Begin Source File

SOURCE=..\string\src\regexp.cpp
# End Source File
# Begin Source File

SOURCE=..\sync\src\rfifo.cpp
# End Source File
# Begin Source File

SOURCE=..\sync\src\rpriority.cpp
# End Source File
# Begin Source File

SOURCE=..\time\src\rule.cpp
# End Source File
# Begin Source File

SOURCE=..\sync\src\rwsem.cpp
# End Source File
# Begin Source File

SOURCE=..\except\src\security_ex.cpp
# End Source File
# Begin Source File

SOURCE=..\sync\src\sfifo.cpp
# End Source File
# Begin Source File

SOURCE=..\io\src\sid.cpp
# End Source File
# Begin Source File

SOURCE=..\time\src\simple.cpp
# End Source File
# Begin Source File

SOURCE=..\sync\src\smutex.cpp
# End Source File
# Begin Source File

SOURCE=..\sync\src\spriority.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"StdAfx.h"
# End Source File
# Begin Source File

SOURCE=..\time\src\stopwtch.cpp
# End Source File
# Begin Source File

SOURCE=..\stream\src\strbuf.cpp
# End Source File
# Begin Source File

SOURCE=..\except\src\stream_ex.cpp
# End Source File
# Begin Source File

SOURCE=..\string\src\strhash.cpp
# End Source File
# Begin Source File

SOURCE=..\string\src\string.cpp
# End Source File
# Begin Source File

SOURCE=..\stream\src\strmdev.cpp
# End Source File
# Begin Source File

SOURCE=..\stream\src\strminit.cpp
# End Source File
# Begin Source File

SOURCE=..\thread\src\thisthrd.cpp
# End Source File
# Begin Source File

SOURCE=..\thread\src\thread.cpp
# End Source File
# Begin Source File

SOURCE=..\except\src\thread_ex.cpp
# End Source File
# Begin Source File

SOURCE=..\time\src\time.cpp
# End Source File
# Begin Source File

SOURCE=..\except\src\time_ex.cpp
# End Source File
# Begin Source File

SOURCE=..\time\src\timedate.cpp
# End Source File
# Begin Source File

SOURCE=..\time\src\timezone.cpp
# End Source File
# Begin Source File

SOURCE=..\string\src\tokenize.cpp
# End Source File
# Begin Source File

SOURCE=..\time\src\tperiod.cpp
# End Source File
# Begin Source File

SOURCE=..\stl\src\treeaux.cpp
# End Source File
# Begin Source File

SOURCE=..\stream\src\tstream.cpp
# End Source File
# Begin Source File

SOURCE=..\time\src\typedefs.cpp
# End Source File
# Begin Source File

SOURCE=..\stl\src\vector.cpp
# End Source File
# Begin Source File

SOURCE=..\type\src\wint.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=..\thread\_info.h
# End Source File
# Begin Source File

SOURCE=..\io\_startup.h
# End Source File
# Begin Source File

SOURCE=..\string\_startup.h
# End Source File
# Begin Source File

SOURCE=..\thread\_startup.h
# End Source File
# Begin Source File

SOURCE=..\io\adapter.h
# End Source File
# Begin Source File

SOURCE=..\io\adapter.ipp
# End Source File
# Begin Source File

SOURCE=..\stl\advalgo.cc
# End Source File
# Begin Source File

SOURCE=..\stl\advalgo.h
# End Source File
# Begin Source File

SOURCE=..\std\algorithm
# End Source File
# Begin Source File

SOURCE=..\stl\allocate.cc
# End Source File
# Begin Source File

SOURCE=..\stl\allocate.h
# End Source File
# Begin Source File

SOURCE=..\stl\allocimp.h
# End Source File
# Begin Source File

SOURCE=..\utility\arrayptr.h
# End Source File
# Begin Source File

SOURCE=..\stream\ascii.h
# End Source File
# Begin Source File

SOURCE=..\stl\auxalgo.cc
# End Source File
# Begin Source File

SOURCE=..\stl\auxalgo.h
# End Source File
# Begin Source File

SOURCE=..\stl\basalgo.cc
# End Source File
# Begin Source File

SOURCE=..\stl\basalgo.h
# End Source File
# Begin Source File

SOURCE=..\string\basic.cc
# End Source File
# Begin Source File

SOURCE=..\string\basic.h
# End Source File
# Begin Source File

SOURCE=..\string\basic.ipp
# End Source File
# Begin Source File

SOURCE=..\stream\bstream.h
# End Source File
# Begin Source File

SOURCE=..\stream\bstream.ipp
# End Source File
# Begin Source File

SOURCE=..\io\bufdev.h
# End Source File
# Begin Source File

SOURCE=..\io\bufdev.ipp
# End Source File
# Begin Source File

SOURCE=..\io\buffer.h
# End Source File
# Begin Source File

SOURCE=..\io\buffer.ipp
# End Source File
# Begin Source File

SOURCE=..\io\cache.h
# End Source File
# Begin Source File

SOURCE=..\io\cache.ipp
# End Source File
# Begin Source File

SOURCE=..\internal\call.h
# End Source File
# Begin Source File

SOURCE=..\rtti\cast.h
# End Source File
# Begin Source File

SOURCE=..\rtti\cast.ipp
# End Source File
# Begin Source File

SOURCE=..\rtti\class.h
# End Source File
# Begin Source File

SOURCE=..\rtti\class.ipp
# End Source File
# Begin Source File

SOURCE=..\rtti\classdb.h
# End Source File
# Begin Source File

SOURCE=..\stl\common.h
# End Source File
# Begin Source File

SOURCE=..\config.h
# End Source File
# Begin Source File

SOURCE=..\except\config.h
# End Source File
# Begin Source File

SOURCE=..\stl\config.h
# End Source File
# Begin Source File

SOURCE=..\string\config.h
# End Source File
# Begin Source File

SOURCE=..\sync\counting.h
# End Source File
# Begin Source File

SOURCE=..\sync\counting.ipp
# End Source File
# Begin Source File

SOURCE=..\sync\critical.h
# End Source File
# Begin Source File

SOURCE=..\sync\critical.ipp
# End Source File
# Begin Source File

SOURCE=..\io\device.h
# End Source File
# Begin Source File

SOURCE=..\io\device.ipp
# End Source File
# Begin Source File

SOURCE=..\internal\errno.h
# End Source File
# Begin Source File

SOURCE=..\internal\error.h
# End Source File
# Begin Source File

SOURCE=..\sync\eventsem.h
# End Source File
# Begin Source File

SOURCE=..\sync\eventsem.ipp
# End Source File
# Begin Source File

SOURCE=..\except\except.h
# End Source File
# Begin Source File

SOURCE=..\extern.h
# End Source File
# Begin Source File

SOURCE=..\internal\fmacros.h
# End Source File
# Begin Source File

SOURCE=..\std\fstream
# End Source File
# Begin Source File

SOURCE=..\stream\fstrmdev.h
# End Source File
# Begin Source File

SOURCE=..\stream\fstrmdev.ipp
# End Source File
# Begin Source File

SOURCE=..\stl\function.h
# End Source File
# Begin Source File

SOURCE=..\stl\heap.cc
# End Source File
# Begin Source File

SOURCE=..\stl\heap.h
# End Source File
# Begin Source File

SOURCE=..\except\helper.h
# End Source File
# Begin Source File

SOURCE=..\except\helper.ipp
# End Source File
# Begin Source File

SOURCE=..\rtti\info.h
# End Source File
# Begin Source File

SOURCE=..\stl\internal.h
# End Source File
# Begin Source File

SOURCE=..\except\io.h
# End Source File
# Begin Source File

SOURCE=..\except\io.ipp
# End Source File
# Begin Source File

SOURCE=..\io\iocontrl.h
# End Source File
# Begin Source File

SOURCE=..\io\iocontrl.ipp
# End Source File
# Begin Source File

SOURCE=..\std\iosfwd
# End Source File
# Begin Source File

SOURCE=..\io\iostatus.h
# End Source File
# Begin Source File

SOURCE=..\io\iostatus.ipp
# End Source File
# Begin Source File

SOURCE=..\std\iostream
# End Source File
# Begin Source File

SOURCE=..\std\istream
# End Source File
# Begin Source File

SOURCE=..\stream\istrmdev.h
# End Source File
# Begin Source File

SOURCE=..\stream\istrmdev.ipp
# End Source File
# Begin Source File

SOURCE=..\stl\iterator.cc
# End Source File
# Begin Source File

SOURCE=..\stl\iterator.h
# End Source File
# Begin Source File

SOURCE=..\std\list
# End Source File
# Begin Source File

SOURCE=..\stl\list.cc
# End Source File
# Begin Source File

SOURCE=..\stl\list.h
# End Source File
# Begin Source File

SOURCE=..\sync\lock.h
# End Source File
# Begin Source File

SOURCE=..\sync\lock.ipp
# End Source File
# Begin Source File

SOURCE=..\std\map
# End Source File
# Begin Source File

SOURCE=..\stl\map.cc
# End Source File
# Begin Source File

SOURCE=..\stl\map.h
# End Source File
# Begin Source File

SOURCE=..\utility\memory.h
# End Source File
# Begin Source File

SOURCE=..\sync\mutex.h
# End Source File
# Begin Source File

SOURCE=..\sync\mutex.ipp
# End Source File
# Begin Source File

SOURCE=..\stream\ndr.h
# End Source File
# Begin Source File

SOURCE=..\stream\ndr.ipp
# End Source File
# Begin Source File

SOURCE=..\stream\ndrlabel.h
# End Source File
# Begin Source File

SOURCE=..\stream\ndrlabel.ipp
# End Source File
# Begin Source File

SOURCE=..\stream\ndrtypes.h
# End Source File
# Begin Source File

SOURCE=..\stl\nodealoc.cc
# End Source File
# Begin Source File

SOURCE=..\stl\nodealoc.h
# End Source File
# Begin Source File

SOURCE=..\COM\OLESTREA.H
# End Source File
# Begin Source File

SOURCE=..\OLESTREA.H
# End Source File
# Begin Source File

SOURCE=..\io\openctrl.h
# End Source File
# Begin Source File

SOURCE=..\io\openctrl.ipp
# End Source File
# Begin Source File

SOURCE=..\stl\ops.h
# End Source File
# Begin Source File

SOURCE=..\std\ostream
# End Source File
# Begin Source File

SOURCE=..\stream\ostrmdev.h
# End Source File
# Begin Source File

SOURCE=..\stream\ostrmdev.ipp
# End Source File
# Begin Source File

SOURCE=..\stl\pair.h
# End Source File
# Begin Source File

SOURCE=..\type\prim.h
# End Source File
# Begin Source File

SOURCE=..\thread\priority.h
# End Source File
# Begin Source File

SOURCE=..\stream\protocol.h
# End Source File
# Begin Source File

SOURCE=..\stream\protocol.ipp
# End Source File
# Begin Source File

SOURCE=..\std\queue
# End Source File
# Begin Source File

SOURCE=..\stl\queue.h
# End Source File
# Begin Source File

SOURCE=..\stl\randgen.h
# End Source File
# Begin Source File

SOURCE=..\stl\rawalgo.cc
# End Source File
# Begin Source File

SOURCE=..\stl\rawalgo.h
# End Source File
# Begin Source File

SOURCE=..\stl\rawiter.h
# End Source File
# Begin Source File

SOURCE=..\stl\rbtree.cc
# End Source File
# Begin Source File

SOURCE=..\stl\rbtree.h
# End Source File
# Begin Source File

SOURCE=..\string\src\regex.h
# End Source File
# Begin Source File

SOURCE=..\string\regexp.h
# End Source File
# Begin Source File

SOURCE=..\string\regexp.ipp
# End Source File
# Begin Source File

SOURCE=..\sync\rfifo.h
# End Source File
# Begin Source File

SOURCE=..\sync\rfifoimp.h
# End Source File
# Begin Source File

SOURCE=..\sync\rprioimp.h
# End Source File
# Begin Source File

SOURCE=..\sync\rpriority.h
# End Source File
# Begin Source File

SOURCE=..\sync\rwsem.h
# End Source File
# Begin Source File

SOURCE=..\sync\rwsem.ipp
# End Source File
# Begin Source File

SOURCE=..\string\search.cc
# End Source File
# Begin Source File

SOURCE=..\string\search.h
# End Source File
# Begin Source File

SOURCE=..\sync\sfifo.h
# End Source File
# Begin Source File

SOURCE=..\sync\sfifoimp.h
# End Source File
# Begin Source File

SOURCE=..\io\sid.h
# End Source File
# Begin Source File

SOURCE=..\sync\simple.h
# End Source File
# Begin Source File

SOURCE=..\stl\sort.cc
# End Source File
# Begin Source File

SOURCE=..\stl\sort.h
# End Source File
# Begin Source File

SOURCE=..\sync\sprioimp.h
# End Source File
# Begin Source File

SOURCE=..\sync\spriority.h
# End Source File
# Begin Source File

SOURCE=..\std\sstream
# End Source File
# Begin Source File

SOURCE=..\except\stdex.h
# End Source File
# Begin Source File

SOURCE=..\std\stdexcept
# End Source File
# Begin Source File

SOURCE=..\stl\stlerror.h
# End Source File
# Begin Source File

SOURCE=..\stream\strbuf.h
# End Source File
# Begin Source File

SOURCE=..\stream\strbuf.ipp
# End Source File
# Begin Source File

SOURCE=..\except\stream.h
# End Source File
# Begin Source File

SOURCE=..\except\stream.ipp
# End Source File
# Begin Source File

SOURCE=..\string\strhash.h
# End Source File
# Begin Source File

SOURCE=..\std\string
# End Source File
# Begin Source File

SOURCE=..\string\string.h
# End Source File
# Begin Source File

SOURCE=..\stream\strmaux.h
# End Source File
# Begin Source File

SOURCE=..\stream\strmaux.ipp
# End Source File
# Begin Source File

SOURCE=..\stream\strmdev.h
# End Source File
# Begin Source File

SOURCE=..\stream\strmdev.ipp
# End Source File
# Begin Source File

SOURCE=..\stream\strmmap.h
# End Source File
# Begin Source File

SOURCE=..\string\substr.cc
# End Source File
# Begin Source File

SOURCE=..\string\substr.h
# End Source File
# Begin Source File

SOURCE=..\string\substr.ipp
# End Source File
# Begin Source File

SOURCE=..\internal\syscall.h
# End Source File
# Begin Source File

SOURCE=..\stl\tempbuf.cc
# End Source File
# Begin Source File

SOURCE=..\stl\tempbuf.h
# End Source File
# Begin Source File

SOURCE=..\thread\thisthrd.h
# End Source File
# Begin Source File

SOURCE=..\except\thread.h
# End Source File
# Begin Source File

SOURCE=..\thread\thread.h
# End Source File
# Begin Source File

SOURCE=..\except\thread.ipp
# End Source File
# Begin Source File

SOURCE=..\thread\thread.ipp
# End Source File
# Begin Source File

SOURCE=..\except\throw.h
# End Source File
# Begin Source File

SOURCE=..\string\tokenize.h
# End Source File
# Begin Source File

SOURCE=..\string\tokenize.ipp
# End Source File
# Begin Source File

SOURCE=..\except\toolkit.h
# End Source File
# Begin Source File

SOURCE=..\except\toolkit.ipp
# End Source File
# Begin Source File

SOURCE=..\string\traits.cc
# End Source File
# Begin Source File

SOURCE=..\string\traits.h
# End Source File
# Begin Source File

SOURCE=..\stl\treeaux.h
# End Source File
# Begin Source File

SOURCE=..\stream\tstream.h
# End Source File
# Begin Source File

SOURCE=..\stream\tstream.ipp
# End Source File
# Begin Source File

SOURCE=..\std\typeinfo
# End Source File
# Begin Source File

SOURCE=..\io\types.h
# End Source File
# Begin Source File

SOURCE=..\thread\types.h
# End Source File
# Begin Source File

SOURCE=..\type\types.h
# End Source File
# Begin Source File

SOURCE=..\std\utility
# End Source File
# Begin Source File

SOURCE=..\std\vector
# End Source File
# Begin Source File

SOURCE=..\stl\vector.cc
# End Source File
# Begin Source File

SOURCE=..\stl\vector.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
