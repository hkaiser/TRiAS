# Microsoft Developer Studio Project File - Name="Esnecil" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Esnecil - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Esnecil.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Esnecil.mak" CFG="Esnecil - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Esnecil - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Esnecil - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/TRiAS/TRiAS/Esnecil", REHBAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Esnecil - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "DLL" /Yu"stdafx.h" /Fd"Release/Esnecil.pdb" /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
# Begin Custom Build
OutDir=.\Release
TargetPath=.\Release\Esnecil.lib
TargetName=Esnecil
InputPath=.\Release\Esnecil.lib
SOURCE="$(InputPath)"

"$(TRIASLIB) \$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASLIB) 
	xcopy /F $(OutDir)\$(TargetName).pdb $(TRIASLIB) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Esnecil - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "DLL" /Yu"stdafx.h" /Fd"Debug/Esnecild.pdb" /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Debug\Esnecild.lib"
# Begin Custom Build
OutDir=.\Debug
TargetPath=.\Debug\Esnecild.lib
TargetName=Esnecild
InputPath=.\Debug\Esnecild.lib
SOURCE="$(InputPath)"

"$(TRIASLIB) \$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASLIB) 
	xcopy /F $(OutDir)\$(TargetName).pdb $(TRIASLIB) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "Esnecil - Win32 Release"
# Name "Esnecil - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Esnecil.cpp
# End Source File
# Begin Source File

SOURCE=.\EsnecilExt.cpp
# End Source File
# Begin Source File

SOURCE=.\EsnecilFlexLm.cpp

!IF  "$(CFG)" == "Esnecil - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Esnecil - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\Include\Esnecil.h
# End Source File
# Begin Source File

SOURCE=.\EsnecilConfig.h
# End Source File
# Begin Source File

SOURCE=..\Include\EsnecilExt.h
# End Source File
# Begin Source File

SOURCE=..\Include\EsnecilFlexLm.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.tpl,*.mak"
# Begin Source File

SOURCE=.\EsnecilVersion.h
# End Source File
# Begin Source File

SOURCE=.\EsnecilVersion.tpl

!IF  "$(CFG)" == "Esnecil - Win32 Release"

USERDEP__ESNEC="version.mak"	
# Begin Custom Build
InputPath=.\EsnecilVersion.tpl

"EsnecilVersion.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak EsnecilVersion.h

# End Custom Build

!ELSEIF  "$(CFG)" == "Esnecil - Win32 Debug"

USERDEP__ESNEC="version.mak"	
# Begin Custom Build
InputPath=.\EsnecilVersion.tpl

"EsnecilVersion.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak EsnecilVersion.h

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\version.mak
# End Source File
# End Group
# End Target
# End Project
