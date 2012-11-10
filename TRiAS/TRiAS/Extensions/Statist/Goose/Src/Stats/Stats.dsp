# Microsoft Developer Studio Project File - Name="Stats" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Stats - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Stats.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Stats.mak" CFG="Stats - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Stats - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Stats - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Stats", BTAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Stats - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /Zi /O1 /I "../.." /I "." /I "../Util" /I "../Specfns" /I "../Containers" /I "../Linear" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /Fd"Release/Stats.pdb" /FD /c
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
TargetPath=.\Release\Stats.lib
TargetName=Stats
InputPath=.\Release\Stats.lib
SOURCE="$(InputPath)"

BuildCmds= \
	xcopy /F $(TargetPath) ..\..\Lib \
	xcopy /F $(OutDir)\$(TargetName).pdb ..\..\Lib \
	

"..\..\Lib\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\Lib\$(TargetName).pdb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Stats - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "../.." /I "." /I "../Util" /I "../Specfns" /I "../Containers" /I "../Linear" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /Fd"Debug/StatsD.pdb" /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Debug\StatsD.lib"
# Begin Custom Build
OutDir=.\Debug
TargetPath=.\Debug\StatsD.lib
TargetName=StatsD
InputPath=.\Debug\StatsD.lib
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

# Name "Stats - Win32 Release"
# Name "Stats - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\bootstrap.cpp
# End Source File
# Begin Source File

SOURCE=.\descriptive.cpp
# End Source File
# Begin Source File

SOURCE=.\fit.cpp
# End Source File
# Begin Source File

SOURCE=.\jackknife.cpp
# End Source File
# Begin Source File

SOURCE=.\KernelDE.cpp
# End Source File
# Begin Source File

SOURCE=.\LinearRegression.cpp
# End Source File
# Begin Source File

SOURCE=.\MetaCurve.cpp
# End Source File
# Begin Source File

SOURCE=.\moving_average.cpp
# End Source File
# Begin Source File

SOURCE=.\normal.cpp
# End Source File
# Begin Source File

SOURCE=.\normality_testing.cpp
# End Source File
# Begin Source File

SOURCE=.\parametric_estimation.cpp
# End Source File
# Begin Source File

SOURCE=.\PolynomialRegression.cpp
# End Source File
# Begin Source File

SOURCE=.\runs.cpp
# End Source File
# Begin Source File

SOURCE=.\wilcoxon.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\bootstrap.h
# End Source File
# Begin Source File

SOURCE=..\..\config.h
# End Source File
# Begin Source File

SOURCE=..\Util\ConfInt.h
# End Source File
# Begin Source File

SOURCE=..\Util\constants.h
# End Source File
# Begin Source File

SOURCE=..\Util\DataConverter.h
# End Source File
# Begin Source File

SOURCE=..\Containers\DataSet.h
# End Source File
# Begin Source File

SOURCE=.\descriptive.h
# End Source File
# Begin Source File

SOURCE=..\Util\Exception.h
# End Source File
# Begin Source File

SOURCE=.\fit.h
# End Source File
# Begin Source File

SOURCE=..\Linear\gala.h
# End Source File
# Begin Source File

SOURCE=.\jackknife.h
# End Source File
# Begin Source File

SOURCE=.\KernelDE.h
# End Source File
# Begin Source File

SOURCE=.\LinearRegression.h
# End Source File
# Begin Source File

SOURCE=.\MetaCurve.h
# End Source File
# Begin Source File

SOURCE=.\moving_average.h
# End Source File
# Begin Source File

SOURCE=.\normal.h
# End Source File
# Begin Source File

SOURCE=.\normality_testing.h
# End Source File
# Begin Source File

SOURCE=.\parametric_estimation.h
# End Source File
# Begin Source File

SOURCE=..\Util\Permutation.h
# End Source File
# Begin Source File

SOURCE=.\PolynomialRegression.h
# End Source File
# Begin Source File

SOURCE=..\Util\Random.h
# End Source File
# Begin Source File

SOURCE=..\Util\RCArray.h
# End Source File
# Begin Source File

SOURCE=..\Util\RCMatrix.h
# End Source File
# Begin Source File

SOURCE=..\Containers\RealSet.h
# End Source File
# Begin Source File

SOURCE=.\runs.h
# End Source File
# Begin Source File

SOURCE=..\Specfns\specfns.h
# End Source File
# Begin Source File

SOURCE=..\Specfns\specfns_protos.h
# End Source File
# Begin Source File

SOURCE=..\Util\stringtools.h
# End Source File
# Begin Source File

SOURCE=.\wilcoxon.h
# End Source File
# End Group
# End Target
# End Project
