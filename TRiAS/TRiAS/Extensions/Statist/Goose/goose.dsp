# Microsoft Developer Studio Project File - Name="goose" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=goose - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "goose.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "goose.mak" CFG="goose - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "goose - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "goose - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "goose - Win32 Debug DLL" (based on "Win32 (x86) Static Library")
!MESSAGE "goose - Win32 Release DLL" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Gooze", CRAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "goose - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "goose___Win32_Debug"
# PROP BASE Intermediate_Dir "goose___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /Gi /GX /ZI /Od /I "src/containers" /I "src/linear" /I "src/specfns" /I "src/stats" /I "src/util" /I "src/win32" /D "WIN32" /D "_AFXDLL" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /Gi /GX /Zi /Od /I "d:\Toolkit\ospace\std" /I "." /I "src/containers" /I "src/linear" /I "src/specfns" /I "src/stats" /I "src/util" /I "src/win32" /D "WIN32" /D "DEBUG" /D "_DEBUG" /FR /Fp"Debug/goosed.pch" /YX /Fd"Debug/goosed.pdb" /FD /GZ /c
# ADD BASE RSC /l 0x406 /d "_DEBUG"
# ADD RSC /l 0x406 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Debug\goosed.lib"

!ELSEIF  "$(CFG)" == "goose - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "goose___Win32_Release"
# PROP BASE Intermediate_Dir "goose___Win32_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /Gm /Gi /GX /ZI /O2 /Ob2 /I "src/containers" /I "src/linear" /I "src/specfns" /I "src/stats" /I "src/util" /I "src/win32" /D "WIN32" /D "_AFXDLL" /YX /FD /GZ /c
# ADD CPP /nologo /MT /W3 /Gi /GX /Zi /O2 /Ob2 /I "d:\Toolkit\ospace\std" /I "." /I "src/containers" /I "src/linear" /I "src/specfns" /I "src/stats" /I "src/util" /I "src/win32" /D "WIN32" /D "NDEBUG" /Fp"Release/gooser.pch" /YX /Fd"Release/gooser.pdb" /FD /c
# ADD BASE RSC /l 0x406 /d "_DEBUG"
# ADD RSC /l 0x406 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Release\gooser.lib"

!ELSEIF  "$(CFG)" == "goose - Win32 Debug DLL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "goose___Win32_Debug_DLL"
# PROP BASE Intermediate_Dir "goose___Win32_Debug_DLL"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug_DLL"
# PROP Intermediate_Dir "Debug_DLL"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /Gi /GX /ZI /Od /I "src/containers" /I "src/linear" /I "src/specfns" /I "src/stats" /I "src/util" /I "src/win32" /D "WIN32" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /Gi /GX /ZI /Od /I "src/containers" /I "src/linear" /I "src/specfns" /I "src/stats" /I "src/util" /I "src/win32" /D "WIN32" /D "_AFXDLL" /YX /FD /GZ /c
# ADD BASE RSC /l 0x406 /d "_DEBUG"
# ADD RSC /l 0x406 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "goose - Win32 Release DLL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "goose___Win32_Release_DLL"
# PROP BASE Intermediate_Dir "goose___Win32_Release_DLL"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Release_DLL"
# PROP Intermediate_Dir "Release_DLL"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /Gi /GX /ZI /Od /I "src/containers" /I "src/linear" /I "src/specfns" /I "src/stats" /I "src/u"
# ADD CPP /nologo /MD /W3 /Gm /Gi /GX /ZI /O2 /Ob2 /I "src/containers" /I "src/linear" /I "src/specfns" /I "src/stats" /I "s"
# ADD BASE RSC /l 0x406 /d "_DEBUG"
# ADD RSC /l 0x406 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "goose - Win32 Debug"
# Name "goose - Win32 Release"
# Name "goose - Win32 Debug DLL"
# Name "goose - Win32 Release DLL"
# Begin Group "src"

# PROP Default_Filter ""
# Begin Group "containers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\containers\AsciiImport.cpp
# End Source File
# Begin Source File

SOURCE=.\src\containers\AsciiImport.h
# End Source File
# Begin Source File

SOURCE=.\src\containers\AsciiReader.cpp
# End Source File
# Begin Source File

SOURCE=.\src\containers\AsciiReader.h
# End Source File
# Begin Source File

SOURCE=.\src\containers\CategoricalSet.cpp
# End Source File
# Begin Source File

SOURCE=.\src\containers\CategoricalSet.h
# End Source File
# Begin Source File

SOURCE=.\src\containers\Category.cpp
# End Source File
# Begin Source File

SOURCE=.\src\containers\Category.h
# End Source File
# Begin Source File

SOURCE=.\src\containers\ColumnDivider.cpp
# End Source File
# Begin Source File

SOURCE=.\src\containers\ColumnDivider.h
# End Source File
# Begin Source File

SOURCE=.\src\containers\DataSet.cpp
# End Source File
# Begin Source File

SOURCE=.\src\containers\DataSet.h
# End Source File
# Begin Source File

SOURCE=.\src\containers\DateSet.cpp
# End Source File
# Begin Source File

SOURCE=.\src\containers\DateSet.h
# End Source File
# Begin Source File

SOURCE=.\src\containers\HoleSet.cpp
# End Source File
# Begin Source File

SOURCE=.\src\containers\HoleSet.h
# End Source File
# Begin Source File

SOURCE=.\src\containers\RealSet.cpp
# End Source File
# Begin Source File

SOURCE=.\src\containers\RealSet.h
# End Source File
# Begin Source File

SOURCE=.\src\containers\StringSet.cpp
# End Source File
# Begin Source File

SOURCE=.\src\containers\StringSet.h
# End Source File
# End Group
# Begin Group "linear"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\linear\gala.cpp
# End Source File
# Begin Source File

SOURCE=.\src\linear\gala.h
# End Source File
# End Group
# Begin Group "specfns"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\specfns\bdtr.cpp
# End Source File
# Begin Source File

SOURCE=.\src\specfns\btdtr.cpp
# End Source File
# Begin Source File

SOURCE=.\src\specfns\chdtr.cpp
# End Source File
# Begin Source File

SOURCE=.\src\specfns\choose.cpp
# End Source File
# Begin Source File

SOURCE=.\src\specfns\const.cpp
# End Source File
# Begin Source File

SOURCE=.\src\specfns\fdtr.cpp
# End Source File
# Begin Source File

SOURCE=.\src\specfns\gamma.cpp
# End Source File
# Begin Source File

SOURCE=.\src\specfns\gdtr.cpp
# End Source File
# Begin Source File

SOURCE=.\src\specfns\hypergeom.cpp
# End Source File
# Begin Source File

SOURCE=.\src\specfns\igam.cpp
# End Source File
# Begin Source File

SOURCE=.\src\specfns\igami.cpp
# End Source File
# Begin Source File

SOURCE=.\src\specfns\incbet.cpp
# End Source File
# Begin Source File

SOURCE=.\src\specfns\incbi.cpp
# End Source File
# Begin Source File

SOURCE=.\src\specfns\mconf.h
# End Source File
# Begin Source File

SOURCE=.\src\specfns\mtherr.cpp
# End Source File
# Begin Source File

SOURCE=.\src\specfns\nbdtr.cpp
# End Source File
# Begin Source File

SOURCE=.\src\specfns\ndtr.cpp
# End Source File
# Begin Source File

SOURCE=.\src\specfns\ndtri.cpp
# End Source File
# Begin Source File

SOURCE=.\src\specfns\pdtr.cpp
# End Source File
# Begin Source File

SOURCE=.\src\specfns\specfns.h
# End Source File
# Begin Source File

SOURCE=.\src\specfns\specfns_protos.h
# End Source File
# Begin Source File

SOURCE=.\src\specfns\stdtr.cpp
# End Source File
# Begin Source File

SOURCE=.\src\specfns\unity.cpp
# End Source File
# End Group
# Begin Group "stats"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\stats\bootstrap.cpp
# End Source File
# Begin Source File

SOURCE=.\src\stats\bootstrap.h
# End Source File
# Begin Source File

SOURCE=.\src\stats\CochranQ.cpp
# End Source File
# Begin Source File

SOURCE=.\src\stats\CochranQ.h
# End Source File
# Begin Source File

SOURCE=.\src\stats\descriptive.cpp
# End Source File
# Begin Source File

SOURCE=.\src\stats\descriptive.h
# End Source File
# Begin Source File

SOURCE=.\src\stats\fit.cpp
# End Source File
# Begin Source File

SOURCE=.\src\stats\fit.h
# End Source File
# Begin Source File

SOURCE=.\src\stats\jackknife.cpp
# End Source File
# Begin Source File

SOURCE=.\src\stats\jackknife.h
# End Source File
# Begin Source File

SOURCE=.\src\stats\KernelDE.cpp
# End Source File
# Begin Source File

SOURCE=.\src\stats\KernelDE.h
# End Source File
# Begin Source File

SOURCE=.\src\stats\kolmogorov_smirnov.cpp
# End Source File
# Begin Source File

SOURCE=.\src\stats\kolmogorov_smirnov.h
# End Source File
# Begin Source File

SOURCE=.\src\stats\Kruskal_Wallis.cpp
# End Source File
# Begin Source File

SOURCE=.\src\stats\Kruskal_Wallis.h
# End Source File
# Begin Source File

SOURCE=.\src\stats\LinearRegression.cpp
# End Source File
# Begin Source File

SOURCE=.\src\stats\LinearRegression.h
# End Source File
# Begin Source File

SOURCE=.\src\stats\McNemar.cpp
# End Source File
# Begin Source File

SOURCE=.\src\stats\McNemar.h
# End Source File
# Begin Source File

SOURCE=.\src\stats\MetaCurve.cpp
# End Source File
# Begin Source File

SOURCE=.\src\stats\MetaCurve.h
# End Source File
# Begin Source File

SOURCE=.\src\stats\moving_average.cpp
# End Source File
# Begin Source File

SOURCE=.\src\stats\moving_average.h
# End Source File
# Begin Source File

SOURCE=.\src\stats\normal.cpp
# End Source File
# Begin Source File

SOURCE=.\src\stats\normal.h
# End Source File
# Begin Source File

SOURCE=.\src\stats\normality_testing.cpp
# End Source File
# Begin Source File

SOURCE=.\src\stats\normality_testing.h
# End Source File
# Begin Source File

SOURCE=.\src\stats\parametric_estimation.cpp
# End Source File
# Begin Source File

SOURCE=.\src\stats\parametric_estimation.h
# End Source File
# Begin Source File

SOURCE=.\src\stats\PolynomialRegression.cpp
# End Source File
# Begin Source File

SOURCE=.\src\stats\PolynomialRegression.h
# End Source File
# Begin Source File

SOURCE=.\src\stats\runs.cpp
# End Source File
# Begin Source File

SOURCE=.\src\stats\runs.h
# End Source File
# Begin Source File

SOURCE=.\src\stats\Spearman.cpp
# End Source File
# Begin Source File

SOURCE=.\src\stats\Spearman.h
# End Source File
# Begin Source File

SOURCE=.\src\stats\StatsDB.cpp
# End Source File
# Begin Source File

SOURCE=.\src\stats\StatsDB.h
# End Source File
# Begin Source File

SOURCE=.\src\stats\wilcoxon.cpp
# End Source File
# Begin Source File

SOURCE=.\src\stats\wilcoxon.h
# End Source File
# End Group
# Begin Group "util"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\util\ConfInt.h
# End Source File
# Begin Source File

SOURCE=.\src\util\constants.h
# End Source File
# Begin Source File

SOURCE=.\src\util\DataConverter.cpp
# End Source File
# Begin Source File

SOURCE=.\src\util\DataConverter.h
# End Source File
# Begin Source File

SOURCE=.\src\util\Exception.cpp
# End Source File
# Begin Source File

SOURCE=.\src\util\Exception.h
# End Source File
# Begin Source File

SOURCE=.\src\util\goose.cpp
# End Source File
# Begin Source File

SOURCE=.\src\util\Permutation.cpp
# End Source File
# Begin Source File

SOURCE=.\src\util\Permutation.h
# End Source File
# Begin Source File

SOURCE=.\src\util\Progress.h
# End Source File
# Begin Source File

SOURCE=.\src\util\Random.cpp
# End Source File
# Begin Source File

SOURCE=.\src\util\Random.h
# End Source File
# Begin Source File

SOURCE=.\src\util\RCArray.h
# End Source File
# Begin Source File

SOURCE=.\src\util\RCMatrix.h
# End Source File
# Begin Source File

SOURCE=.\src\util\stringtools.cpp
# End Source File
# Begin Source File

SOURCE=.\src\util\stringtools.h
# End Source File
# Begin Source File

SOURCE=.\src\util\WarningController.h
# End Source File
# Begin Source File

SOURCE=.\src\util\zdouble.cpp
# End Source File
# Begin Source File

SOURCE=.\src\util\zdouble.h
# End Source File
# End Group
# Begin Group "win32"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\config.h
# End Source File
# End Group
# End Group
# End Target
# End Project
