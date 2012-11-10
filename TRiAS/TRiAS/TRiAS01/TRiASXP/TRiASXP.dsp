# Microsoft Developer Studio Project File - Name="TRiASXP" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=TRiASXP - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TRiASXP.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TRiASXP.mak" CFG="TRiASXP - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TRiASXP - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "TRiASXP - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=xicl6.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TRiASXP - Win32 Release"

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
F90=fl32.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "C:\PROGRAMME\MICROSOFT SQL SERVER\80\TOOLS\DEVTOOLS\INCLUDE" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"StdAfx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 opends60.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386

!ELSEIF  "$(CFG)" == "TRiASXP - Win32 Debug"

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
F90=fl32.exe
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "C:\PROGRAMME\MICROSOFT SQL SERVER\80\TOOLS\DEVTOOLS\INCLUDE" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"StdAfx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 opends60.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# Begin Custom Build
OutDir=.\Debug
TargetPath=.\Debug\TRiASXP.dll
TargetName=TRiASXP
InputPath=.\Debug\TRiASXP.dll
SOURCE="$(InputPath)"

"D:\Program Files\Microsoft SQL Server\MSSQL\Binn\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) "D:\Program Files\Microsoft SQL Server\MSSQL\Binn" 
	xcopy /F "$(OutDir)\$(TargetName).pdb" "D:\Program Files\Microsoft SQL Server\MSSQL\Binn" 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "TRiASXP - Win32 Release"
# Name "TRiASXP - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "TRiASXP - Win32 Release"

# ADD CPP /Yc"StdAfx.h"

!ELSEIF  "$(CFG)" == "TRiASXP - Win32 Debug"

# ADD CPP /MDd /Yc"StdAfx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TRiASXP.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASXP.def
# End Source File
# Begin Source File

SOURCE=.\TRiASXP.rc
# End Source File
# Begin Source File

SOURCE=.\xp_AsText.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ErrorUtils.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TRiASXPConfig.h
# End Source File
# Begin Source File

SOURCE=.\Wrapper.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.tpl,*.mak"
# Begin Source File

SOURCE=.\TRiASXP.tpl

!IF  "$(CFG)" == "TRiASXP - Win32 Release"

USERDEP__TRIAS="version.mak"	
# Begin Custom Build
InputPath=.\TRiASXP.tpl

"TRiASXP.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak TRiASXP.def

# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASXP - Win32 Debug"

USERDEP__TRIAS="version.mak"	
# Begin Custom Build
InputPath=.\TRiASXP.tpl

"TRiASXP.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak TRiASXP.def

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TRiASXPv.tpl

!IF  "$(CFG)" == "TRiASXP - Win32 Release"

USERDEP__TRIASX="version.mak"	
# Begin Custom Build
InputPath=.\TRiASXPv.tpl

"TRiASXP.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak TRiASXP.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASXP - Win32 Debug"

USERDEP__TRIASX="version.mak"	
# Begin Custom Build
InputPath=.\TRiASXPv.tpl

"TRiASXP.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak TRiASXP.rcv

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Version.mak
# End Source File
# Begin Source File

SOURCE=.\Version.tpl

!IF  "$(CFG)" == "TRiASXP - Win32 Release"

USERDEP__VERSI="version.mak"	
# Begin Custom Build
InputPath=.\Version.tpl

"Version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak Version.h

# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASXP - Win32 Debug"

USERDEP__VERSI="version.mak"	
# Begin Custom Build
InputPath=.\Version.tpl

"Version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak Version.h

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Test Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TRiASXPFree.sql
# End Source File
# Begin Source File

SOURCE=.\TRiASXPInstall.sql
# End Source File
# End Group
# End Target
# End Project
