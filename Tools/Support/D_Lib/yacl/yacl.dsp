# Microsoft Developer Studio Project File - Name="yacl" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=yacl - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "yacl.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "yacl.mak" CFG="yacl - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "yacl - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "yacl - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "yacl - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "$(YACLPATH)" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "__MS_WIN32__" /YX /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Release\yaclbasr.lib"

!ELSEIF  "$(CFG)" == "yacl - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ  /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "$(YACLPATH)" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "__MS_WIN32__" /YX /FD /GZ  /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Debug\yaclbasd.lib"

!ENDIF 

# Begin Target

# Name "yacl - Win32 Release"
# Name "yacl - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\base\bitset.cxx
# End Source File
# Begin Source File

SOURCE=.\base\bytarray.cxx
# End Source File
# Begin Source File

SOURCE=.\base\bytestrm.cxx
# End Source File
# Begin Source File

SOURCE=.\base\bytstrng.cxx
# End Source File
# Begin Source File

SOURCE=.\base\clntset.cxx
# End Source File
# Begin Source File

SOURCE=.\base\date.cxx
# End Source File
# Begin Source File

SOURCE=.\base\error.cxx
# End Source File
# Begin Source File

SOURCE=.\base\gbtree.cxx
# End Source File
# Begin Source File

SOURCE=.\base\genseq.cxx
# End Source File
# Begin Source File

SOURCE=.\base\integer.cxx
# End Source File
# Begin Source File

SOURCE=.\base\intseq.cxx
# End Source File
# Begin Source File

SOURCE=.\base\intset.cxx
# End Source File
# Begin Source File

SOURCE=.\base\map.cxx
# End Source File
# Begin Source File

SOURCE=.\base\object.cxx
# End Source File
# Begin Source File

SOURCE=.\base\objseq.cxx
# End Source File
# Begin Source File

SOURCE=.\base\objset.cxx
# End Source File
# Begin Source File

SOURCE=.\base\regexpr.cxx
# End Source File
# Begin Source File

SOURCE=.\base\segseq.cxx
# End Source File
# Begin Source File

SOURCE=.\base\stream.cxx
# End Source File
# Begin Source File

SOURCE=.\base\strgseq.cxx
# End Source File
# Begin Source File

SOURCE=.\base\strgset.cxx
# End Source File
# Begin Source File

SOURCE=.\base\string.cxx
# End Source File
# Begin Source File

SOURCE=.\base\strsplit.cxx
# End Source File
# Begin Source File

SOURCE=.\base\tbtree.cxx
# End Source File
# Begin Source File

SOURCE=.\base\timeofda.cxx
# End Source File
# Begin Source File

SOURCE=.\base\tree.cxx
# End Source File
# Begin Source File

SOURCE=.\base\treewalk.cxx
# End Source File
# Begin Source File

SOURCE=.\base\version.cxx
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\base\base.h
# End Source File
# Begin Source File

SOURCE=.\base\basicops.h
# End Source File
# Begin Source File

SOURCE=.\base\binding.h
# End Source File
# Begin Source File

SOURCE=.\base\bitset.h
# End Source File
# Begin Source File

SOURCE=.\base\bordll.h
# End Source File
# Begin Source File

SOURCE=.\base\builder.h
# End Source File
# Begin Source File

SOURCE=.\base\bytarray.h
# End Source File
# Begin Source File

SOURCE=.\base\bytestrm.h
# End Source File
# Begin Source File

SOURCE=.\base\bytstrng.h
# End Source File
# Begin Source File

SOURCE=.\base\classid.h
# End Source File
# Begin Source File

SOURCE=.\base\clntset.h
# End Source File
# Begin Source File

SOURCE=.\base\cmparatr.h
# End Source File
# Begin Source File

SOURCE=.\base\date.h
# End Source File
# Begin Source File

SOURCE=.\base\defs.h
# End Source File
# Begin Source File

SOURCE=.\base\error.h
# End Source File
# Begin Source File

SOURCE=.\base\gbtree.h
# End Source File
# Begin Source File

SOURCE=.\base\genseq.h
# End Source File
# Begin Source File

SOURCE=.\base\hashtbl.h
# End Source File
# Begin Source File

SOURCE=.\base\integer.h
# End Source File
# Begin Source File

SOURCE=.\base\intseq.h
# End Source File
# Begin Source File

SOURCE=.\base\intset.h
# End Source File
# Begin Source File

SOURCE=.\base\iterator.h
# End Source File
# Begin Source File

SOURCE=.\base\long.h
# End Source File
# Begin Source File

SOURCE=.\base\map.h
# End Source File
# Begin Source File

SOURCE=.\base\mapdef.h
# End Source File
# Begin Source File

SOURCE=.\base\memory.h
# End Source File
# Begin Source File

SOURCE=.\base\msvcdll.h
# End Source File
# Begin Source File

SOURCE=.\base\object.h
# End Source File
# Begin Source File

SOURCE=.\base\objptr.h
# End Source File
# Begin Source File

SOURCE=.\base\objseq.h
# End Source File
# Begin Source File

SOURCE=.\base\objset.h
# End Source File
# Begin Source File

SOURCE=.\base\regexpr.h
# End Source File
# Begin Source File

SOURCE=.\base\segseq.h
# End Source File
# Begin Source File

SOURCE=.\base\sequence.h
# End Source File
# Begin Source File

SOURCE=.\base\set.h
# End Source File
# Begin Source File

SOURCE=.\base\setdef.h
# End Source File
# Begin Source File

SOURCE=.\base\stream.h
# End Source File
# Begin Source File

SOURCE=.\base\strgseq.h
# End Source File
# Begin Source File

SOURCE=.\base\strgset.h
# End Source File
# Begin Source File

SOURCE=.\base\string.h
# End Source File
# Begin Source File

SOURCE=.\base\strsplit.h
# End Source File
# Begin Source File

SOURCE=.\base\tbtree.h
# End Source File
# Begin Source File

SOURCE=.\base\timeofda.h
# End Source File
# Begin Source File

SOURCE=.\base\tree.h
# End Source File
# Begin Source File

SOURCE=.\base\treedef.h
# End Source File
# Begin Source File

SOURCE=.\base\treewalk.h
# End Source File
# Begin Source File

SOURCE=.\base\treewdef.h
# End Source File
# Begin Source File

SOURCE=.\base\version.h
# End Source File
# Begin Source File

SOURCE=.\base\voidptr.h
# End Source File
# End Group
# End Target
# End Project
