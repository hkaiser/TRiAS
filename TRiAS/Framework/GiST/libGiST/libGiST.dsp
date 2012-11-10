# Microsoft Developer Studio Project File - Name="libGiST" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=libGiST - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libGiST.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libGiST.mak" CFG="libGiST - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libGiST - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libGiST - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=xicl6.exe
RSC=rc.exe

!IF  "$(CFG)" == "libGiST - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O2 /I "..\libGiST" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /YX /Fd".\Release/libGiST.pdb" /FD /c
# ADD BASE RSC /l 0x407
# ADD RSC /l 0x407
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
# Begin Custom Build
OutDir=.\Release
TargetPath=.\Release\libGiST.lib
TargetName=libGiST
InputPath=.\Release\libGiST.lib
InputName=libGiST
SOURCE="$(InputPath)"

"$(TRIASLIB)\$(InputName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /f $(TargetPath) $(TRIASLIB) 
	xcopy /f $(OutDir)\$(TargetName).pdb $(TRIASLIB) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "libGiST - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W3 /WX /GX /Zi /Od /I "..\libGiST" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /YX /Fd".\Debug/libGiSTd.pdb" /FD /c
# ADD BASE RSC /l 0x407
# ADD RSC /l 0x407
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:".\Debug\libGiSTd.lib"
# Begin Custom Build
OutDir=.\Debug
TargetPath=.\Debug\libGiSTd.lib
TargetName=libGiSTd
InputPath=.\Debug\libGiSTd.lib
SOURCE="$(InputPath)"

"$(TRIASLIB)\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /f $(TargetPath) $(TRIASLIB) 
	xcopy /f $(OutDir)\$(TargetName).pdb $(TRIASLIB) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "libGiST - Win32 Release"
# Name "libGiST - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\GiST.cpp
# End Source File
# Begin Source File

SOURCE=.\GiSTcursor.cpp
# End Source File
# Begin Source File

SOURCE=.\GiSTfile.cpp
# End Source File
# Begin Source File

SOURCE=.\GiSTnode.cpp
# End Source File
# Begin Source File

SOURCE=.\GiSTpredicate.cpp
# End Source File
# Begin Source File

SOURCE=..\RSTree\RT.cpp
# End Source File
# Begin Source File

SOURCE=..\RSTree\RTentry.cpp
# End Source File
# Begin Source File

SOURCE=..\RSTree\RTnode.cpp
# End Source File
# Begin Source File

SOURCE=..\RSTree\RTpredicate.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\GiST.h
# End Source File
# Begin Source File

SOURCE=.\GiSTcursor.h
# End Source File
# Begin Source File

SOURCE=.\GiSTdefs.h
# End Source File
# Begin Source File

SOURCE=.\GiSTentry.h
# End Source File
# Begin Source File

SOURCE=.\GiSTfile.h
# End Source File
# Begin Source File

SOURCE=.\GiSTlist.h
# End Source File
# Begin Source File

SOURCE=.\GiSTnode.h
# End Source File
# Begin Source File

SOURCE=.\GiSTpath.h
# End Source File
# Begin Source File

SOURCE=.\GiSTpredicate.h
# End Source File
# Begin Source File

SOURCE=.\GiSTstore.h
# End Source File
# Begin Source File

SOURCE=..\RSTree\RT.h
# End Source File
# Begin Source File

SOURCE=..\RSTree\RTentry.h
# End Source File
# Begin Source File

SOURCE=..\RSTree\RTnode.h
# End Source File
# Begin Source File

SOURCE=..\RSTree\RTpredicate.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
