# Microsoft Developer Studio Project File - Name="GbmTRiAS" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=GbmTRiAS - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "GbmTRiAS.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "GbmTRiAS.mak" CFG="GbmTRiAS - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GbmTRiAS - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "GbmTRiAS - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "GbmTRiAS - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "__XT" /D "__MFC__" /D "__DEXPROCS" /Fr /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ixtmfr42.lib cont32r.lib stdcppr.lib /nologo /subsystem:windows /dll /machine:I386 /out:".\Release\GbmTRiAS.ext"

!ELSEIF  "$(CFG)" == "GbmTRiAS - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "__XT" /D "__MFC__" /D "__DEXPROCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 ixtmfd40.lib cont32d.lib stdcppd.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"F:\Trias200\TRiAS_Debug/GbmTRiAd.ext"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "GbmTRiAS - Win32 Release"
# Name "GbmTRiAS - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\About.cpp
# End Source File
# Begin Source File

SOURCE=.\DLDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\EdPage1.cpp
# End Source File
# Begin Source File

SOURCE=.\EdPage2.cpp
# End Source File
# Begin Source File

SOURCE=.\EdPage3.cpp
# End Source File
# Begin Source File

SOURCE=.\EdPage4.cpp
# End Source File
# Begin Source File

SOURCE=.\EdPage5.cpp
# End Source File
# Begin Source File

SOURCE=.\EdPage6.cpp
# End Source File
# Begin Source File

SOURCE=.\GbmTRiAS.cpp
# End Source File
# Begin Source File

SOURCE=.\GbmTRiAS.def
# End Source File
# Begin Source File

SOURCE=.\GbmTRiAS.rc

!IF  "$(CFG)" == "GbmTRiAS - Win32 Release"

!ELSEIF  "$(CFG)" == "GbmTRiAS - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MyPropS.cpp
# End Source File
# Begin Source File

SOURCE=.\NF_PG1.cpp
# End Source File
# Begin Source File

SOURCE=.\NF_PG1FL.cpp
# End Source File
# Begin Source File

SOURCE=.\NF_PG1GB.cpp
# End Source File
# Begin Source File

SOURCE=.\NF_PG2D.cpp
# End Source File
# Begin Source File

SOURCE=.\NF_PG2H.cpp
# End Source File
# Begin Source File

SOURCE=.\OpProDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\OrteSet.cpp
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\SetOI.cpp
# End Source File
# Begin Source File

SOURCE=.\SetSI.cpp
# End Source File
# Begin Source File

SOURCE=.\SPage1.cpp
# End Source File
# Begin Source File

SOURCE=.\SPage2.cpp
# End Source File
# Begin Source File

SOURCE=.\StatDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StrasseSet.cpp
# End Source File
# Begin Source File

SOURCE=.\SuchPage0.cpp
# End Source File
# Begin Source File

SOURCE=.\SuchPage1.cpp
# End Source File
# Begin Source File

SOURCE=.\SuchPage2.cpp
# End Source File
# Begin Source File

SOURCE=.\SuchPage3.cpp
# End Source File
# Begin Source File

SOURCE=.\SuchPage4.cpp
# End Source File
# Begin Source File

SOURCE=.\SuchResDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\TriDBSet.cpp
# End Source File
# Begin Source File

SOURCE=.\VerzSet.cpp
# End Source File
# Begin Source File

SOURCE=.\VerzSet2.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Util\Xstring.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\About.h
# End Source File
# Begin Source File

SOURCE=.\DLDlg.h
# End Source File
# Begin Source File

SOURCE=.\EdPage1.h
# End Source File
# Begin Source File

SOURCE=.\EdPage2.h
# End Source File
# Begin Source File

SOURCE=.\EdPage3.h
# End Source File
# Begin Source File

SOURCE=.\EdPage4.h
# End Source File
# Begin Source File

SOURCE=.\EdPage5.h
# End Source File
# Begin Source File

SOURCE=.\EdPage6.h
# End Source File
# Begin Source File

SOURCE=.\Gbmguid.h
# End Source File
# Begin Source File

SOURCE=.\GbmTRiAS.h
# End Source File
# Begin Source File

SOURCE=.\MyPropS.h
# End Source File
# Begin Source File

SOURCE=.\NF_PG1.h
# End Source File
# Begin Source File

SOURCE=.\NF_PG1FL.h
# End Source File
# Begin Source File

SOURCE=.\NF_PG1GB.h
# End Source File
# Begin Source File

SOURCE=.\NF_PG2D.h
# End Source File
# Begin Source File

SOURCE=.\NF_PG2H.h
# End Source File
# Begin Source File

SOURCE=.\OpProDlg.h
# End Source File
# Begin Source File

SOURCE=.\OrteSet.h
# End Source File
# Begin Source File

SOURCE=.\SetOI.h
# End Source File
# Begin Source File

SOURCE=.\SetSI.h
# End Source File
# Begin Source File

SOURCE=.\SPage1.h
# End Source File
# Begin Source File

SOURCE=.\SPage2.h
# End Source File
# Begin Source File

SOURCE=.\Stat1Dlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\StrasseSet.h
# End Source File
# Begin Source File

SOURCE=.\SuchPage0.h
# End Source File
# Begin Source File

SOURCE=.\SuchPage1.h
# End Source File
# Begin Source File

SOURCE=.\SuchPage2.h
# End Source File
# Begin Source File

SOURCE=.\SuchPage3.h
# End Source File
# Begin Source File

SOURCE=.\SuchPage4.h
# End Source File
# Begin Source File

SOURCE=.\SuchResDlg.h
# End Source File
# Begin Source File

SOURCE=.\TriDBSet.h
# End Source File
# Begin Source File

SOURCE=.\Versio16.h
# End Source File
# Begin Source File

SOURCE=.\Versio32.h
# End Source File
# Begin Source File

SOURCE=.\Version.h
# End Source File
# Begin Source File

SOURCE=.\VerzSet.h
# End Source File
# Begin Source File

SOURCE=.\VerzSet2.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\bitmap3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GbmTRiAS.rc2
# End Source File
# End Group
# End Target
# End Project
