# Microsoft Developer Studio Project File - Name="standards uss" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=standards uss - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "standards uss.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "standards uss.mak" CFG="standards uss - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "standards uss - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "standards uss - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "standards uss - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\standards uss\Release"
# PROP BASE Intermediate_Dir ".\standards uss\Release"
# PROP BASE Target_Dir ".\standards uss"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\RelUss"
# PROP Intermediate_Dir ".\RelUss"
# PROP Target_Dir ".\standards uss"
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /GR /GX /Z7 /O1 /D "NDEBUG" /D "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS" /D "OS_WIN_95" /D "WIN32" /D "_WINDOWS" /D "OS_STL_ASSERT" /D "OS_ALTERNATIVE_STRING_NAMES" /YX /FD /c
# ADD BASE RSC /l 0x407
# ADD RSC /l 0x407
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:".\RelUss\StdStr5r.lib"
# Begin Custom Build - Copying Target to Destination ...
TargetPath=.\RelUss\StdStr5r.lib
TargetName=StdStr5r
InputPath=.\RelUss\StdStr5r.lib
SOURCE="$(InputPath)"

"$(TRIASLIB)\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(TargetPath) $(TRIASLIB)

# End Custom Build

!ELSEIF  "$(CFG)" == "standards uss - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\standards uss\Debug"
# PROP BASE Intermediate_Dir ".\standards uss\Debug"
# PROP BASE Target_Dir ".\standards uss"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\DebugUss"
# PROP Intermediate_Dir ".\DebugUss"
# PROP Target_Dir ".\standards uss"
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /D "_DEBUG" /D "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS" /D "OS_WIN_95" /D "WIN32" /D "_WINDOWS" /D "OS_STL_ASSERT" /D "OS_ALTERNATIVE_STRING_NAMES" /YX /FD /c
# ADD BASE RSC /l 0x407
# ADD RSC /l 0x407
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:".\DebugUss\StdStr5d.lib"
# Begin Custom Build - Copying Target to Destination ...
TargetPath=.\DebugUss\StdStr5d.lib
TargetName=StdStr5d
InputPath=.\DebugUss\StdStr5d.lib
SOURCE="$(InputPath)"

"$(TRIASLIB)\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASLIB)

# End Custom Build

!ENDIF 

# Begin Target

# Name "standards uss - Win32 Release"
# Name "standards uss - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=..\uss\file\src\file_uss.cpp
# End Source File
# Begin Source File

SOURCE=..\uss\std\src\std_uss.cpp
# End Source File
# Begin Source File

SOURCE=..\uss\time\src\time_uss.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=..\io\adapter.h
# End Source File
# Begin Source File

SOURCE=..\io\adapter.ipp
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

SOURCE=..\stl\common.h
# End Source File
# Begin Source File

SOURCE=..\config.h
# End Source File
# Begin Source File

SOURCE=..\stl\config.h
# End Source File
# Begin Source File

SOURCE=..\string\config.h
# End Source File
# Begin Source File

SOURCE=..\internal\fmacros.h
# End Source File
# Begin Source File

SOURCE=..\header.h
# End Source File
# Begin Source File

SOURCE=..\rtti\hmacros.h
# End Source File
# Begin Source File

SOURCE=..\stream\hmacros.h
# End Source File
# Begin Source File

SOURCE=..\rtti\hmacros1.h
# End Source File
# Begin Source File

SOURCE=..\rtti\hmacros3.h
# End Source File
# Begin Source File

SOURCE=..\uss\id.h
# End Source File
# Begin Source File

SOURCE=..\uss\std\id.h
# End Source File
# Begin Source File

SOURCE=..\std\iosfwd
# End Source File
# Begin Source File

SOURCE=..\std\istream
# End Source File
# Begin Source File

SOURCE=..\stl\iterator.cc
# End Source File
# Begin Source File

SOURCE=..\stl\iterator.h
# End Source File
# Begin Source File

SOURCE=..\utility\memory.h
# End Source File
# Begin Source File

SOURCE=..\stl\ops.h
# End Source File
# Begin Source File

SOURCE=..\std\ostream
# End Source File
# Begin Source File

SOURCE=..\stl\pair.h
# End Source File
# Begin Source File

SOURCE=..\type\prim.h
# End Source File
# Begin Source File

SOURCE=..\stream\protocol.h
# End Source File
# Begin Source File

SOURCE=..\stream\protocol.ipp
# End Source File
# Begin Source File

SOURCE=..\rtti\regmacro.h
# End Source File
# Begin Source File

SOURCE=..\rtti\rtti.h
# End Source File
# Begin Source File

SOURCE=..\stream\rtti.h
# End Source File
# Begin Source File

SOURCE=..\string\search.cc
# End Source File
# Begin Source File

SOURCE=..\string\search.h
# End Source File
# Begin Source File

SOURCE=..\rtti\smacros.h
# End Source File
# Begin Source File

SOURCE=..\stream\smacros.h
# End Source File
# Begin Source File

SOURCE=..\stl\stlerror.h
# End Source File
# Begin Source File

SOURCE=..\std\string
# End Source File
# Begin Source File

SOURCE=..\string\string.h
# End Source File
# Begin Source File

SOURCE=..\uss\std\string.h
# End Source File
# Begin Source File

SOURCE=..\string\traits.cc
# End Source File
# Begin Source File

SOURCE=..\string\traits.h
# End Source File
# Begin Source File

SOURCE=..\std\typeinfo
# End Source File
# Begin Source File

SOURCE=..\type\types.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
