# Microsoft Developer Studio Project File - Name="Specfns" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Specfns - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Specfns.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Specfns.mak" CFG="Specfns - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Specfns - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Specfns - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Gooze/Specfns", CSAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Specfns - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /Zi /O1 /I "../.." /I "." /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /Fd"Release/Specfns.pdb" /FD /c
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
TargetPath=.\Release\Specfns.lib
TargetName=Specfns
InputPath=.\Release\Specfns.lib
SOURCE="$(InputPath)"

BuildCmds= \
	xcopy /F $(TargetPath) ..\..\Lib \
	xcopy /F $(OutDir)\$(TargetName).pdb ..\..\Lib \
	

"..\..\Lib\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\Lib\$(TargetName).pdb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Specfns - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "../.." /I "." /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /Fd"Debug/Specfnsd.pdb" /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Debug\SpecfnsD.lib"
# Begin Custom Build
OutDir=.\Debug
TargetPath=.\Debug\SpecfnsD.lib
TargetName=SpecfnsD
InputPath=.\Debug\SpecfnsD.lib
SOURCE="$(InputPath)"

BuildCmds= \
	xcopy /F $(TargetPath) ..\..\Lib \
	xcopy /F $(OutDir)\$(TargetName).pdb ..\..\Lib \
	

"..\..\Lib\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\Lib\$(TargetName).pdb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# Begin Target

# Name "Specfns - Win32 Release"
# Name "Specfns - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\bdtr.cpp
# End Source File
# Begin Source File

SOURCE=.\btdtr.cpp
# End Source File
# Begin Source File

SOURCE=.\chdtr.cpp
# End Source File
# Begin Source File

SOURCE=.\choose.cpp
# End Source File
# Begin Source File

SOURCE=.\const.cpp
# End Source File
# Begin Source File

SOURCE=.\fdtr.cpp
# End Source File
# Begin Source File

SOURCE=.\gamma.cpp
# End Source File
# Begin Source File

SOURCE=.\gdtr.cpp
# End Source File
# Begin Source File

SOURCE=.\igam.cpp
# End Source File
# Begin Source File

SOURCE=.\igami.cpp
# End Source File
# Begin Source File

SOURCE=.\incbet.cpp
# End Source File
# Begin Source File

SOURCE=.\incbi.cpp
# End Source File
# Begin Source File

SOURCE=.\mtherr.cpp
# End Source File
# Begin Source File

SOURCE=.\nbdtr.cpp
# End Source File
# Begin Source File

SOURCE=.\ndtr.cpp
# End Source File
# Begin Source File

SOURCE=.\ndtri.cpp
# End Source File
# Begin Source File

SOURCE=.\pdtr.cpp
# End Source File
# Begin Source File

SOURCE=.\stdtr.cpp
# End Source File
# Begin Source File

SOURCE=.\unity.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\config.h
# End Source File
# Begin Source File

SOURCE=.\mconf.h
# End Source File
# Begin Source File

SOURCE=.\specfns.h
# End Source File
# Begin Source File

SOURCE=.\specfns_protos.h
# End Source File
# End Group
# End Target
# End Project
