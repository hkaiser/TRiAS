# Microsoft Developer Studio Project File - Name="Shapelib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Shapelib - Win32 Debug True Time
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Shapelib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Shapelib.mak" CFG="Shapelib - Win32 Debug True Time"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Shapelib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Shapelib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "Shapelib - Win32 Debug True Time" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/TRiAS/TRiASDB/TRiASHP/Shapelib", FRDBAAAA"
# PROP Scc_LocalPath "."
CPP=xicl6.exe
RSC=rc.exe

!IF  "$(CFG)" == "Shapelib - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /Zi /O1 /I ".\Proj.4" /I "." /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "_LITTLE_ENDIAN" /D "PROJ4" /YX /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
# Begin Custom Build
OutDir=.\Release
TargetPath=.\Release\Shapelib.lib
TargetName=Shapelib
InputPath=.\Release\Shapelib.lib
SOURCE="$(InputPath)"

"$(TRIASLIB)/$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASLIB) 
	xcopy /F "$(OutDir)/$(TargetName).lib" $(TRIASLIB) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Shapelib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Shapelib___Win32_Debug"
# PROP BASE Intermediate_Dir "Shapelib___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Shapelib___Win32_Debug"
# PROP Intermediate_Dir "Shapelib___Win32_Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I ".\Proj.4" /I "." /D "_LIB" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LITTLE_ENDIAN" /D "PROJ4" /YX /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Shapelib___Win32_Debug\Shapelibd.lib"
# Begin Custom Build
OutDir=.\Shapelib___Win32_Debug
TargetPath=.\Shapelib___Win32_Debug\Shapelibd.lib
TargetName=Shapelibd
InputPath=.\Shapelib___Win32_Debug\Shapelibd.lib
SOURCE="$(InputPath)"

"$(TRIASLIB)/$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASLIB) 
	xcopy /F "$(OutDir)/$(TargetName).lib" $(TRIASLIB) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Shapelib - Win32 Debug True Time"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Shapelib___Win32_Debug_True_Time"
# PROP BASE Intermediate_Dir "Shapelib___Win32_Debug_True_Time"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Shapelib___Win32_Debug_True_Time"
# PROP Intermediate_Dir "Shapelib___Win32_Debug_True_Time"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I ".\Proj.4" /I "." /D "_LIB" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LITTLE_ENDIAN" /D "PROJ4" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /GX /ZI /Od /I ".\Proj.4" /I "." /D "_LIB" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LITTLE_ENDIAN" /D "PROJ4" /YX /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "Shapelib - Win32 Release"
# Name "Shapelib - Win32 Debug"
# Name "Shapelib - Win32 Debug True Time"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\dbfopen.c
# End Source File
# Begin Source File

SOURCE=.\contrib\shpgeo.c
# End Source File
# Begin Source File

SOURCE=.\shpopen.c
# End Source File
# Begin Source File

SOURCE=.\shptree.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\shapefil.h
# End Source File
# Begin Source File

SOURCE=.\contrib\shpgeo.h
# End Source File
# End Group
# End Target
# End Project
