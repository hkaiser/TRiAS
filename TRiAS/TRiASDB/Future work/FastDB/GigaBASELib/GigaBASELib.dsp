# Microsoft Developer Studio Project File - Name="GigaBASELib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=GigaBASELib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "GigaBASELib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "GigaBASELib.mak" CFG="GigaBASELib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GigaBASELib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "GigaBASELib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "GigaBASELib - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /Zi /O2 /D "USE_LOCALE_SETTINGS" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "USE_QUEUE_MANAGER" /YX /Fd"Release/GigaBASE.pdb" /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Release\GigaBASE.lib"
# Begin Custom Build
TargetDir=.\Release
TargetPath=.\Release\GigaBASE.lib
TargetName=GigaBASE
InputPath=.\Release\GigaBASE.lib
SOURCE="$(InputPath)"

"$(TRIASLIB)\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASLIB) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASLIB) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "GigaBASELib - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "USE_LOCALE_SETTINGS" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "USE_QUEUE_MANAGER" /YX /Fd"Debug/GigaBASEd.pdb" /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Debug\GigaBASEd.lib"
# Begin Custom Build
TargetDir=.\Debug
TargetPath=.\Debug\GigaBASEd.lib
TargetName=GigaBASEd
InputPath=.\Debug\GigaBASEd.lib
SOURCE="$(InputPath)"

"$(TRIASLIB)\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASLIB) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASLIB) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "GigaBASELib - Win32 Release"
# Name "GigaBASELib - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\btree.cpp
# End Source File
# Begin Source File

SOURCE=.\class.cpp
# End Source File
# Begin Source File

SOURCE=.\compiler.cpp
# End Source File
# Begin Source File

SOURCE=.\cursor.cpp
# End Source File
# Begin Source File

SOURCE=.\database.cpp
# End Source File
# Begin Source File

SOURCE=.\file.cpp
# End Source File
# Begin Source File

SOURCE=.\hashtab.cpp
# End Source File
# Begin Source File

SOURCE=.\pagepool.cpp
# End Source File
# Begin Source File

SOURCE=.\query.cpp
# End Source File
# Begin Source File

SOURCE=.\symtab.cpp
# End Source File
# Begin Source File

SOURCE=.\w32sock.cpp
# End Source File
# Begin Source File

SOURCE=.\wwwapi.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\array.h
# End Source File
# Begin Source File

SOURCE=.\btree.h
# End Source File
# Begin Source File

SOURCE=.\class.h
# End Source File
# Begin Source File

SOURCE=.\compiler.h
# End Source File
# Begin Source File

SOURCE=.\cursor.h
# End Source File
# Begin Source File

SOURCE=.\database.h
# End Source File
# Begin Source File

SOURCE=.\file.h
# End Source File
# Begin Source File

SOURCE=.\gigabase.h
# End Source File
# Begin Source File

SOURCE=.\hashtab.h
# End Source File
# Begin Source File

SOURCE=.\pagepool.h
# End Source File
# Begin Source File

SOURCE=.\query.h
# End Source File
# Begin Source File

SOURCE=.\stdtp.h
# End Source File
# Begin Source File

SOURCE=.\symtab.h
# End Source File
# Begin Source File

SOURCE=.\unisock.h
# End Source File
# Begin Source File

SOURCE=.\w32sock.h
# End Source File
# Begin Source File

SOURCE=.\wwwapi.h
# End Source File
# End Group
# End Target
# End Project
