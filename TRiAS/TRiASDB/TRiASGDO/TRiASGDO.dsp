# Microsoft Developer Studio Project File - Name="TRiASGDO" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=TRiASGDO - Win32 Debug BoundsChecker
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TRiASGDO.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TRiASGDO.mak" CFG="TRiASGDO - Win32 Debug BoundsChecker"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TRiASGDO - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "TRiASGDO - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "TRiASGDO - Win32 Debug TrueTime" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "TRiASGDO - Win32 Debug BoundsChecker" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/TRiAS/TRiAS/GDOEngine", ORLAAAAA"
# PROP Scc_LocalPath "."
CPP=xicl6.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TRiASGDO - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "_Debug"
# PROP Intermediate_Dir "_Debug"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /Gi /GX /Zi /Od /I "$(TRIASDIR_D)" /D "_DEBUG" /D "_USRDLL" /D "WIN32" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /base:"0x017b0000" /subsystem:windows /dll /debug /machine:I386 /out:"_Debug/TRiASGDOD.dll"
# Begin Custom Build
OutDir=.\_Debug
TargetName=TRiASGDOD
InputPath=.\_Debug\TRiASGDOD.dll
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(OutDir)\$(TargetName).dll" "$(TRIASDIR_D)" 
	xcopy /F "$(OutDir)\$(TargetName).pdb" "$(TRIASDIR_D)" 
	
# End Custom Build
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Cmds=nmake -nologo -f Version.mak CFG=_DEBUG VERSION
# End Special Build Tool

!ELSEIF  "$(CFG)" == "TRiASGDO - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "TRiASGDO"
# PROP BASE Intermediate_Dir "TRiASGDO"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "_Release"
# PROP Intermediate_Dir "_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O1 /I "c:/Programme/Geomedia/" /I "e:/Entwickl" /I "$(TRIASDIR_D)" /D "NDEBUG" /D "_ATL_DLL" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "__ATL_USED__" /D "QI_EXCEPTION" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "NOMINMAX" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D "OS_NO_STREAM_SUPPORT" /D "OS_NO_ALLOCATORS" /D "__ATL_20_USED__" /D "ATL_NO_NAMESPACE" /D GM_INSTALL_PATH="c:/Programme/Geomedia/" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /Od /D "_WINDOWS" /D "WIN32" /D "NDEBUG" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# Begin Custom Build
OutDir=.\_Release
TargetName=TRiASGDO
InputPath=.\_Release\TRiASGDO.dll
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(OutDir)\$(TargetName).dll" "$(TRIASDIR_R)" 
	xcopy /F "$(OutDir)\$(TargetName).pdb" "$(TRIASDIR_R)" 
	
# End Custom Build
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Cmds=nmake -nologo -f Version.mak CFG=NDEBUG VERSION
# End Special Build Tool

!ELSEIF  "$(CFG)" == "TRiASGDO - Win32 Debug TrueTime"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "TRiASGDO___Win32_Debug_TrueTime"
# PROP BASE Intermediate_Dir "TRiASGDO___Win32_Debug_TrueTime"
# PROP BASE Ignore_Export_Lib 1
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "TRiASGDO___Win32_Debug_TrueTime"
# PROP Intermediate_Dir "TRiASGDO___Win32_Debug_TrueTime"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MDd /W3 /WX /Gm /Gi /GX /Zi /Od /I "$(TRIASDIR_D)" /D "_DEBUG" /D "_USRDLL" /D "WIN32" /D "_WINDOWS" /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /Gi /GX /Zi /Od /I "$(TRIASDIR_D)" /D "_DEBUG" /D "_USRDLL" /D "WIN32" /D "_WINDOWS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /base:"0x017b0000" /subsystem:windows /dll /debug /machine:I386 /out:"_Debug/TRiASGDOD.dll"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /base:"0x017b0000" /subsystem:windows /dll /debug /machine:I386 /out:"TRiASGDO___Win32_Debug_TrueTime/TRiASGDOD.dll"
# Begin Custom Build
OutDir=.\TRiASGDO___Win32_Debug_TrueTime
TargetName=TRiASGDOD
InputPath=.\TRiASGDO___Win32_Debug_TrueTime\TRiASGDOD.dll
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(OutDir)\$(TargetName).dll" "$(TRIASDIR_D)" 
	xcopy /F "$(OutDir)\$(TargetName).pdb" "$(TRIASDIR_D)" 
	
# End Custom Build
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Cmds=nmake -nologo -f Version.mak CFG=_DEBUG VERSION
# End Special Build Tool

!ELSEIF  "$(CFG)" == "TRiASGDO - Win32 Debug BoundsChecker"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "TRiASGDO___Win32_Debug_BoundsChecker"
# PROP BASE Intermediate_Dir "TRiASGDO___Win32_Debug_BoundsChecker"
# PROP BASE Ignore_Export_Lib 1
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "TRiASGDO___Win32_Debug_BoundsChecker"
# PROP Intermediate_Dir "TRiASGDO___Win32_Debug_BoundsChecker"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MDd /W3 /WX /Gm /Gi /GX /Zi /Od /I "$(TRIASDIR_D)" /D "_DEBUG" /D "_USRDLL" /D "WIN32" /D "_WINDOWS" /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /Gi /GX /Zi /Od /I "$(TRIASDIR_D)" /D "_DEBUG" /D "_USRDLL" /D "WIN32" /D "_WINDOWS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /base:"0x017b0000" /subsystem:windows /dll /debug /machine:I386 /out:"_Debug/TRiASGDOD.dll"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /base:"0x017b0000" /subsystem:windows /dll /debug /machine:I386 /out:"TRiASGDO___Win32_Debug_BoundsChecker/TRiASGDOD.dll"
# Begin Custom Build
OutDir=.\TRiASGDO___Win32_Debug_BoundsChecker
TargetName=TRiASGDOD
InputPath=.\TRiASGDO___Win32_Debug_BoundsChecker\TRiASGDOD.dll
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(OutDir)\$(TargetName).dll" "$(TRIASDIR_D)" 
	xcopy /F "$(OutDir)\$(TargetName).pdb" "$(TRIASDIR_D)" 
	
# End Custom Build
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Cmds=nmake -nologo -f Version.mak CFG=_DEBUG VERSION
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "TRiASGDO - Win32 Debug"
# Name "TRiASGDO - Win32 Release"
# Name "TRiASGDO - Win32 Debug TrueTime"
# Name "TRiASGDO - Win32 Debug BoundsChecker"
# Begin Group "TRiASGDO"

# PROP Default_Filter ""
# Begin Group "GDO Database"

# PROP Default_Filter ""
# Begin Group "ITRiASAccessDatabase"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\GDODB_Itad.cpp
# End Source File
# End Group
# Begin Group "ITRiASPropertySupport"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\GDODB_Itps.cpp
# End Source File
# End Group
# Begin Group "IGDOAccess"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\GDODB_IGDOAcc.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\GDODatabase.cpp
# End Source File
# Begin Source File

SOURCE=.\GDODatabase.h
# End Source File
# Begin Source File

SOURCE=.\GDODBEngine.cpp
# End Source File
# Begin Source File

SOURCE=.\GDODBEngine.h
# End Source File
# End Group
# Begin Group "GDO Objects"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\GDOFeature.cpp
# End Source File
# Begin Source File

SOURCE=.\GDOFeature.h
# End Source File
# Begin Source File

SOURCE=.\GDOFeatures.cpp
# End Source File
# Begin Source File

SOURCE=.\GDOFeatures.h
# End Source File
# Begin Source File

SOURCE=.\GDOObject.cpp
# End Source File
# Begin Source File

SOURCE=.\GDOObject.h
# End Source File
# Begin Source File

SOURCE=.\GDOObjects.cpp
# End Source File
# Begin Source File

SOURCE=.\GDOObjects.h
# End Source File
# Begin Source File

SOURCE=.\GDOObjectsColl.cpp
# End Source File
# Begin Source File

SOURCE=.\GDOObjectsColl.h
# End Source File
# End Group
# Begin Group "GMHelpers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\GMHelpers\CSKGeomTypes.h
# End Source File
# End Group
# Begin Group "SQLServer"

# PROP Default_Filter ""
# Begin Group "User Interface"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\PpgSQLServer.cpp
# End Source File
# Begin Source File

SOURCE=.\PpgSQLServer.h
# End Source File
# Begin Source File

SOURCE=.\PpgSQLServerOpenNew.cpp
# End Source File
# Begin Source File

SOURCE=.\PpgSQLServerOpenNew.h
# End Source File
# Begin Source File

SOURCE=.\PropSheetExt2.h
# End Source File
# Begin Source File

SOURCE=.\ReconnectSQLServerDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ReconnectSQLServerDlg.h
# End Source File
# Begin Source File

SOURCE=.\Separator.cpp
# End Source File
# Begin Source File

SOURCE=.\Separator.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\CreateOpenWizPropExt.h
# End Source File
# Begin Source File

SOURCE=.\CreateSQLServerDB.cpp
# End Source File
# Begin Source File

SOURCE=.\CreateSQLServerDB.h
# End Source File
# Begin Source File

SOURCE=.\ReconnectSQLServer.cpp
# End Source File
# Begin Source File

SOURCE=.\ReconnectSQLServer.h
# End Source File
# Begin Source File

SOURCE=.\SQLServerUtils.h
# End Source File
# End Group
# Begin Group "Oracle"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\PPgOracle.cpp
# End Source File
# Begin Source File

SOURCE=.\PPgOracle.h
# End Source File
# Begin Source File

SOURCE=.\PPGOracle.rgs
# End Source File
# End Group
# Begin Source File

SOURCE=.\MapHelpers.h
# End Source File
# Begin Source File

SOURCE=.\Strings.cpp
# End Source File
# Begin Source File

SOURCE=.\Strings.h
# End Source File
# Begin Source File

SOURCE=.\Wrapper.h
# End Source File
# End Group
# Begin Group "DLL Data"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\dlldatax.c
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\dlldatax.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TRiASGDO.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASGDO.idl

!IF  "$(CFG)" == "TRiASGDO - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing MIDL step
InputPath=.\TRiASGDO.idl
InputName=TRiASGDO

BuildCmds= \
	nmake -nologo -f version.mak CFG=_DEBUG

".\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\$(InputName).tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASTLB)\$(InputName).tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASGDO - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing MIDL step
InputPath=.\TRiASGDO.idl
InputName=TRiASGDO

BuildCmds= \
	nmake -nologo -f version.mak CFG=NDEBUG

".\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\$(InputName).tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASTLB)\$(InputName).tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASGDO - Win32 Debug TrueTime"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing MIDL step
InputPath=.\TRiASGDO.idl
InputName=TRiASGDO

BuildCmds= \
	nmake -nologo -f version.mak CFG=_DEBUG

".\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\$(InputName).tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASTLB)\$(InputName).tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASGDO - Win32 Debug BoundsChecker"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing MIDL step
InputPath=.\TRiASGDO.idl
InputName=TRiASGDO

BuildCmds= \
	nmake -nologo -f version.mak CFG=_DEBUG

".\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\$(InputName).tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASTLB)\$(InputName).tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TRiASGDOConfig.h
# End Source File
# Begin Source File

SOURCE=.\TRiASGDOImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASGDOImpl.h
# End Source File
# Begin Source File

SOURCE=.\Version.mak

!IF  "$(CFG)" == "TRiASGDO - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\Version.mak

BuildCmds= \
	nmake -nologo -f version.mak CFG=_DEBUG

".\TRiASGDO.ver" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TRiASGDO.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TRiASGDO.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASGDO - Win32 Release"

# PROP BASE Exclude_From_Build 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\Version.mak

BuildCmds= \
	nmake -nologo -f version.mak CFG=NDEBUG

".\TRiASGDO.ver" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TRiASGDO.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TRiASGDO.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASGDO - Win32 Debug TrueTime"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\Version.mak

BuildCmds= \
	nmake -nologo -f version.mak CFG=_DEBUG

".\TRiASGDO.ver" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TRiASGDO.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TRiASGDO.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASGDO - Win32 Debug BoundsChecker"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\Version.mak

BuildCmds= \
	nmake -nologo -f version.mak CFG=_DEBUG

".\TRiASGDO.ver" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TRiASGDO.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TRiASGDO.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Help Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\TriasDB\DBMSG.MC
# End Source File
# Begin Source File

SOURCE=.\help\TRiASGDO.d

!IF  "$(CFG)" == "TRiASGDO - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\help\TRiASGDO.d
InputName=TRiASGDO

"$(TRIASINCLUDE)\help\$(InputName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak CFG=_DEBUG

# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASGDO - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\help\TRiASGDO.d
InputName=TRiASGDO

"$(TRIASINCLUDE)\help\$(InputName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak CFG=NDEBUG

# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASGDO - Win32 Debug TrueTime"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\help\TRiASGDO.d
InputName=TRiASGDO

"$(TRIASINCLUDE)\help\$(InputName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak CFG=_DEBUG

# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASGDO - Win32 Debug BoundsChecker"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\help\TRiASGDO.d
InputName=TRiASGDO

"$(TRIASINCLUDE)\help\$(InputName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak CFG=_DEBUG

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TRiASGDO.mc

!IF  "$(CFG)" == "TRiASGDO - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\TRiASGDO.mc

BuildCmds= \
	nmake -nologo -f version.mak CFG=_DEBUG

".\TRiASGDO.hmc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\res\msg00407.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\res\msg00409.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASGDO - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\TRiASGDO.mc

BuildCmds= \
	nmake -nologo -f version.mak CFG=NDEBUG

".\TRiASGDO.hmc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\res\msg00407.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\res\msg00409.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASGDO - Win32 Debug TrueTime"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\TRiASGDO.mc

BuildCmds= \
	nmake -nologo -f version.mak CFG=_DEBUG

".\TRiASGDO.hmc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\res\msg00407.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\res\msg00409.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASGDO - Win32 Debug BoundsChecker"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\TRiASGDO.mc

BuildCmds= \
	nmake -nologo -f version.mak CFG=_DEBUG

".\TRiASGDO.hmc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\res\msg00407.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\res\msg00409.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Group "Registry Scripts"

# PROP Default_Filter "Registry Scripts (*.rgs)"
# Begin Source File

SOURCE=.\CreateOpenWizPropExt.rgs
# End Source File
# Begin Source File

SOURCE=.\res\CreateSQLServerDB.rgs
# End Source File
# Begin Source File

SOURCE=.\res\FakeGDOServer.rgs
# End Source File
# Begin Source File

SOURCE=.\res\GDODatabase.rgs
# End Source File
# Begin Source File

SOURCE=.\res\GDODBEngine.rgs
# End Source File
# Begin Source File

SOURCE=.\res\GDOFeature.rgs
# End Source File
# Begin Source File

SOURCE=.\res\GDOFeatures.rgs
# End Source File
# Begin Source File

SOURCE=.\res\GDOObject.rgs
# End Source File
# Begin Source File

SOURCE=.\res\GDOObjects.rgs
# End Source File
# Begin Source File

SOURCE=.\res\GDOObjectsCollection.rgs
# End Source File
# Begin Source File

SOURCE=.\res\GDOTriasDB.rgs
# End Source File
# Begin Source File

SOURCE=.\res\ReconnectSQLServer.rgs
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\msg00407.bin

!IF  "$(CFG)" == "TRiASGDO - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASGDO - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASGDO - Win32 Debug TrueTime"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASGDO - Win32 Debug BoundsChecker"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\MSG00409.bin
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\res\SQLServerMetaData.sql
# End Source File
# Begin Source File

SOURCE=.\res\Topkarte.bmp
# End Source File
# Begin Source File

SOURCE=.\res\TRiASCS.bmp
# End Source File
# Begin Source File

SOURCE=.\TRiASGDO.rc
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "tpl;mak"
# Begin Source File

SOURCE=.\TRiASGDO.def
# End Source File
# Begin Source File

SOURCE=.\TRIASGDO.rcv
# End Source File
# Begin Source File

SOURCE=.\TRiASGDO.ver
# End Source File
# End Group
# Begin Group "Generated Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\_Debug\TDBGeo.tlh

!IF  "$(CFG)" == "TRiASGDO - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASGDO - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASGDO - Win32 Debug TrueTime"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASGDO - Win32 Debug BoundsChecker"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\_Debug\TDBGeoD.tlh

!IF  "$(CFG)" == "TRiASGDO - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASGDO - Win32 Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASGDO - Win32 Debug TrueTime"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASGDO - Win32 Debug BoundsChecker"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\_Debug\TErrTrk.tlh

!IF  "$(CFG)" == "TRiASGDO - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASGDO - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASGDO - Win32 Debug TrueTime"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASGDO - Win32 Debug BoundsChecker"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\_Debug\TRiASCS.tlh

!IF  "$(CFG)" == "TRiASGDO - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASGDO - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASGDO - Win32 Debug TrueTime"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASGDO - Win32 Debug BoundsChecker"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\_Debug\TRiASDB.tlh

!IF  "$(CFG)" == "TRiASGDO - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASGDO - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASGDO - Win32 Debug TrueTime"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASGDO - Win32 Debug BoundsChecker"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TRiASGDO.h

!IF  "$(CFG)" == "TRiASGDO - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASGDO - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASGDO - Win32 Debug TrueTime"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASGDO - Win32 Debug BoundsChecker"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TRiASGDO.hmc

!IF  "$(CFG)" == "TRiASGDO - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASGDO - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASGDO - Win32 Debug TrueTime"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASGDO - Win32 Debug BoundsChecker"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TRiASGDO.tlb

!IF  "$(CFG)" == "TRiASGDO - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASGDO - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASGDO - Win32 Debug TrueTime"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASGDO - Win32 Debug BoundsChecker"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TRiASGDO_i.c

!IF  "$(CFG)" == "TRiASGDO - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASGDO - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASGDO - Win32 Debug TrueTime"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASGDO - Win32 Debug BoundsChecker"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\_Debug\TRiASMDS.tlh

!IF  "$(CFG)" == "TRiASGDO - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASGDO - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASGDO - Win32 Debug TrueTime"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASGDO - Win32 Debug BoundsChecker"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
# Section TRiASGDO : {F08AD9FF-B964-11CF-A19A-08003601D502}
# 	2:5:Class:CDefCoordSystem
# 	2:10:HeaderFile:_defcoordsystem.h
# 	2:8:ImplFile:_defcoordsystem.cpp
# End Section
# Section TRiASGDO : {00410002-0002-0040-0200-3F0002004400}
# 	1:25:IDD_RECONNECTSQLSERVERDLG:135
# End Section
# Section TRiASGDO : {00F7F5F9-0300-30B8-F9F5-F7000003B830}
# 	1:13:IDR_PPGORACLE:124
# 	1:22:IDS_DOCSTRINGPPGOracle:123
# 	1:21:IDS_HELPFILEPPGOracle:122
# 	1:18:IDS_TITLEPPGOracle:121
# 	1:13:IDD_PPGORACLE:125
# End Section
# Section TRiASGDO : {096E591C-632E-6C74-0000-73002E006300}
# 	1:13:IDD_PPGORACLE:120
# End Section
# Section TRiASGDO : {6F696475-435C-6D6F-6D6F-6E5C4D534465}
# 	1:21:IDS_TITLEPpgSQLServer:128
# 	1:16:IDD_PPGSQLSERVER:132
# 	1:24:IDS_HELPFILEPpgSQLServer:129
# 	1:16:IDR_PPGSQLSERVER:131
# 	1:25:IDS_DOCSTRINGPpgSQLServer:130
# End Section
# Section TRiASGDO : {F08AD9F9-B964-11CF-A19A-08003601D502}
# 	2:21:DefaultSinkHeaderFile:_defcoordsystem.h
# 	2:16:DefaultSinkClass:CDefCoordSystem
# End Section
