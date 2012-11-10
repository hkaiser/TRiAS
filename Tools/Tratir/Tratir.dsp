# Microsoft Developer Studio Project File - Name="TRATIR" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=TRATIR - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Tratir.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Tratir.mak" CFG="TRATIR - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TRATIR - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "TRATIR - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TRATIR - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\WinRel"
# PROP BASE Intermediate_Dir ".\WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\WinRel"
# PROP Intermediate_Dir ".\WinRel"
# PROP Ignore_Export_Lib 0
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "_CONSOLE" /D "__ATL_USED__" /D "__ATL_20_USED__" /D "QI_EXCEPTION" /D "WIN32" /Yu"tratasp.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 ospace5r.lib containr.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "TRATIR - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\WinDebug"
# PROP BASE Intermediate_Dir ".\WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\WinDebug"
# PROP Intermediate_Dir ".\WinDebug"
# PROP Ignore_Export_Lib 0
# ADD BASE CPP /nologo /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /ZI /Od /Ob1 /D "_DEBUG" /D "_CONSOLE" /D "__ATL_USED__" /D "__ATL_20_USED__" /D "QI_EXCEPTION" /D "WIN32" /Fr /Yu"tratasp.h" /FD /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 ospace5d.lib cont50d.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /out:".\WinDebug\tratird.exe"

!ENDIF 

# Begin Target

# Name "TRATIR - Win32 Release"
# Name "TRATIR - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\ALTPRSLP.CPP
# End Source File
# Begin Source File

SOURCE=.\ALTPRSYP.CPP
# End Source File
# Begin Source File

SOURCE=.\ATLPARS.LX
# End Source File
# Begin Source File

SOURCE=.\ATLPARS.Y
# End Source File
# Begin Source File

SOURCE=.\ATLPARSL.C
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\ATLPARSY.C
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\FormatString.cpp
# End Source File
# Begin Source File

SOURCE=.\GINHED.CPP
# End Source File
# Begin Source File

SOURCE=.\IGLAGED.CPP
# End Source File
# Begin Source File

SOURCE=.\IGPPTED.CPP
# End Source File
# Begin Source File

SOURCE=.\IGUMOED.CPP
# End Source File
# Begin Source File

SOURCE=.\MTREE.CPP
# End Source File
# Begin Source File

SOURCE=.\TRAT_ASC.CPP
# End Source File
# Begin Source File

SOURCE=.\TRAT_ASM.CPP
# End Source File
# Begin Source File

SOURCE=.\TRATASP.CPP
# ADD CPP /Yc"tratasp.h"
# End Source File
# Begin Source File

SOURCE=.\Tratir.rc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\ATLERRS.H
# End Source File
# Begin Source File

SOURCE=.\ATLPARS.H
# End Source File
# Begin Source File

SOURCE=.\DBVERSIO.H
# End Source File
# Begin Source File

SOURCE=.\MTREE.HXX
# End Source File
# Begin Source File

SOURCE=.\ParamArray.h
# End Source File
# Begin Source File

SOURCE=.\TRATASP.H
# End Source File
# Begin Source File

SOURCE=.\YTAB.H
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\icon1.ico
# End Source File
# End Group
# End Target
# End Project
