# Microsoft Developer Studio Project File - Name="libstdModel" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=libstdModel - Win32 Debug Intel
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libstdModel.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libstdModel.mak" CFG="libstdModel - Win32 Debug Intel"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libstdModel - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libstdModel - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "libstdModel - Win32 Debug Intel" (based on "Win32 (x86) Static Library")
!MESSAGE "libstdModel - Win32 Release Intel" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libstdModel - Win32 Release"

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
F90=df.exe
# ADD BASE F90 /include:"Release/" /compile_only /nologo /warn:nofileopt
# ADD F90 /include:"Release/" /compile_only /nologo /warn:nofileopt
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /Zi /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "OS_NO_ALLOCATORS" /D "OS_WIN_95" /D "OS_MULTI_THREADED" /D "OS_NO_STREAM_SUPPORT" /D "OS_STL_ASSERT" /D "OS_ALTERNATIVE_STRING_NAMES" /D string=os_string /YX /Fd"Release/libstdModel.pdb" /FD /c
# ADD BASE RSC /l 0x407
# ADD RSC /l 0x407
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
# Begin Custom Build
OutDir=.\Release
TargetPath=.\Release\libstdModel.lib
TargetName=libstdModel
InputPath=.\Release\libstdModel.lib
SOURCE="$(InputPath)"

"$(TRIASLIB)\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASLIB) 
	xcopy /F "$(OutDir)\$(TargetName).pdb" $(TRIASLIB) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "libstdModel - Win32 Debug"

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
F90=df.exe
# ADD BASE F90 /include:"Debug/" /compile_only /nologo /debug:full /optimize:0 /warn:nofileopt
# ADD F90 /include:"Debug/" /compile_only /nologo /debug:full /optimize:0 /warn:nofileopt
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /GX /Zi /D "_WINDOWS" /D "WIN32" /D "_DEBUG" /D "OS_NO_ALLOCATORS" /D "OS_WIN_95" /D "OS_MULTI_THREADED" /D "OS_NO_STREAM_SUPPORT" /D "OS_STL_ASSERT" /D "OS_ALTERNATIVE_STRING_NAMES" /D string=os_string /YX /Fd"Debug/libstdModeld.pdb" /FD /TP /c
# ADD BASE RSC /l 0x407
# ADD RSC /l 0x407
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Debug\libstdModeld.lib"
# Begin Custom Build
OutDir=.\Debug
TargetPath=.\Debug\libstdModeld.lib
TargetName=libstdModeld
InputPath=.\Debug\libstdModeld.lib
SOURCE="$(InputPath)"

"$(TRIASLIB)\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASLIB) 
	xcopy /F "$(OutDir)\$(TargetName).pdb" $(TRIASLIB) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "libstdModel - Win32 Debug Intel"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "libstdModel___Win32_Debug_Intel"
# PROP BASE Intermediate_Dir "libstdModel___Win32_Debug_Intel"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "libstdModel___Win32_Debug_Intel"
# PROP Intermediate_Dir "libstdModel___Win32_Debug_Intel"
# PROP Target_Dir ""
F90=df.exe
# ADD BASE F90 /include:"Debug/" /compile_only /nologo /debug:full /optimize:0 /warn:nofileopt
# ADD F90 /include:"Debug/" /compile_only /nologo /debug:full /optimize:0 /warn:nofileopt
# ADD BASE CPP /nologo /MDd /W3 /GX /Zi /D "_WINDOWS" /D "WIN32" /D "_DEBUG" /D "OS_NO_ALLOCATORS" /D "OS_WIN_95" /D "OS_MULTI_THREADED" /D "OS_NO_STREAM_SUPPORT" /D "OS_STL_ASSERT" /D "OS_ALTERNATIVE_STRING_NAMES" /D string=os_string /D "_USE_INTEL_COMPILER" /YX /Fd"Debug/libstdModeld.pdb" /FD /TP /c
# ADD CPP /nologo /MDd /W3 /GX /Zi /D "_WINDOWS" /D "WIN32" /D "_DEBUG" /D "OS_NO_ALLOCATORS" /D "OS_WIN_95" /D "OS_MULTI_THREADED" /D "OS_NO_STREAM_SUPPORT" /D "OS_STL_ASSERT" /D "OS_ALTERNATIVE_STRING_NAMES" /D string=os_string /D "_USE_INTEL_COMPILER" /YX /Fd"libstdModel___Win32_Debug_Intel/libstdModeld.pdb" /FD /TP /c
# ADD BASE RSC /l 0x407
# ADD RSC /l 0x407
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"Debug\libstdModeld.lib"
# ADD LIB32 /nologo /out:"libstdModel___Win32_Debug_Intel\libstdModelIcld.lib"
# Begin Custom Build
OutDir=.\libstdModel___Win32_Debug_Intel
TargetPath=.\libstdModel___Win32_Debug_Intel\libstdModelIcld.lib
TargetName=libstdModelIcld
InputPath=.\libstdModel___Win32_Debug_Intel\libstdModelIcld.lib
SOURCE="$(InputPath)"

"$(TRIASLIB)\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASLIB) 
	rem xcopy /F "$(OutDir)\$(TargetName).pdb" $(TRIASLIB) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "libstdModel - Win32 Release Intel"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "libstdModel___Win32_Release_Intel"
# PROP BASE Intermediate_Dir "libstdModel___Win32_Release_Intel"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "libstdModel___Win32_Release_Intel"
# PROP Intermediate_Dir "libstdModel___Win32_Release_Intel"
# PROP Target_Dir ""
F90=df.exe
# ADD BASE F90 /include:"Release/" /compile_only /nologo /warn:nofileopt
# ADD F90 /include:"Release/" /compile_only /nologo /warn:nofileopt
# ADD BASE CPP /nologo /MD /W3 /GX /Zi /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "OS_NO_ALLOCATORS" /D "OS_WIN_95" /D "OS_MULTI_THREADED" /D "OS_NO_STREAM_SUPPORT" /D "OS_STL_ASSERT" /D "OS_ALTERNATIVE_STRING_NAMES" /D string=os_string /D "_USE_INTEL_COMPILER" /YX /Fd"Release/libstdModel.pdb" /FD /c
# ADD CPP /nologo /MD /W3 /GX /Zi /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "OS_NO_ALLOCATORS" /D "OS_WIN_95" /D "OS_MULTI_THREADED" /D "OS_NO_STREAM_SUPPORT" /D "OS_STL_ASSERT" /D "OS_ALTERNATIVE_STRING_NAMES" /D string=os_string /D "_USE_INTEL_COMPILER" /YX /Fd"Release/libstdModel.pdb" /FD /c
# ADD BASE RSC /l 0x407
# ADD RSC /l 0x407
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"libstdModel___Win32_Release_Intel\libstdModelIcl.lib"
# Begin Custom Build
OutDir=.\libstdModel___Win32_Release_Intel
TargetPath=.\libstdModel___Win32_Release_Intel\libstdModelIcl.lib
TargetName=libstdModelIcl
InputPath=.\libstdModel___Win32_Release_Intel\libstdModelIcl.lib
SOURCE="$(InputPath)"

"$(TRIASLIB)\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASLIB) 
	rem xcopy /F "$(OutDir)\$(TargetName).pdb" $(TRIASLIB) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "libstdModel - Win32 Release"
# Name "libstdModel - Win32 Debug"
# Name "libstdModel - Win32 Debug Intel"
# Name "libstdModel - Win32 Release Intel"
# Begin Source File

SOURCE=..\..\src\std\Model.cpp

!IF  "$(CFG)" == "libstdModel - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "libstdModel - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "libstdModel - Win32 Debug Intel"

!ELSEIF  "$(CFG)" == "libstdModel - Win32 Release Intel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\src\std\NT_Model.cpp

!IF  "$(CFG)" == "libstdModel - Win32 Release"

!ELSEIF  "$(CFG)" == "libstdModel - Win32 Debug"

!ELSEIF  "$(CFG)" == "libstdModel - Win32 Debug Intel"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "libstdModel - Win32 Release Intel"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Target
# End Project
