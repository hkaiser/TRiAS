# Microsoft Developer Studio Project File - Name="CopyDLKW" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=CopyDLKW - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CopyDLKW.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CopyDLKW.mak" CFG="CopyDLKW - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CopyDLKW - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "CopyDLKW - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=xicl6.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CopyDLKW - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"StdAfx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "CopyDLKW - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"StdAfx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "CopyDLKW - Win32 Release"
# Name "CopyDLKW - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CopyDLKThread.cpp
# End Source File
# Begin Source File

SOURCE=.\CopyDLKW.cpp
# End Source File
# Begin Source File

SOURCE=.\CopyDLKW.odl
# End Source File
# Begin Source File

SOURCE=.\CopyDLKW.rc
# End Source File
# Begin Source File

SOURCE=.\CopyDLKWDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DDXGetFolder.cpp
# End Source File
# Begin Source File

SOURCE=.\Boost\directory.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlgdir.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgProxy.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"StdAfx.h"
# End Source File
# Begin Source File

SOURCE=.\Thread.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CopyDLKConfig.h
# End Source File
# Begin Source File

SOURCE=.\CopyDLKThread.h
# End Source File
# Begin Source File

SOURCE=.\CopyDLKW.h
# End Source File
# Begin Source File

SOURCE=.\CopyDLKWDlg.h
# End Source File
# Begin Source File

SOURCE=.\DDXGetFolder.h
# End Source File
# Begin Source File

SOURCE=.\Dlgdir.h
# End Source File
# Begin Source File

SOURCE=.\DlgProxy.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Thread.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\CopyDLKW.ico
# End Source File
# Begin Source File

SOURCE=.\res\CopyDLKW.rc2
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.mak,*.tpl"
# Begin Source File

SOURCE=.\res\CopyDLKv.tpl

!IF  "$(CFG)" == "CopyDLKW - Win32 Release"

USERDEP__COPYD="version.mak"	
# Begin Custom Build
InputPath=.\res\CopyDLKv.tpl

"res\CopyDLK.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f version.mak -nologo res\CopyDLK.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "CopyDLKW - Win32 Debug"

USERDEP__COPYD="version.mak"	
# Begin Custom Build
InputPath=.\res\CopyDLKv.tpl

"res\CopyDLK.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f version.mak -nologo res\CopyDLK.rcv

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\copystrt.tpl

!IF  "$(CFG)" == "CopyDLKW - Win32 Release"

USERDEP__COPYS="version.mak"	
# Begin Custom Build
InputPath=.\res\copystrt.tpl

"res\Copystr.rc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f version.mak -nologo res\Copystr.rc

# End Custom Build

!ELSEIF  "$(CFG)" == "CopyDLKW - Win32 Debug"

USERDEP__COPYS="version.mak"	
# Begin Custom Build
InputPath=.\res\copystrt.tpl

"res\Copystr.rc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f version.mak -nologo res\Copystr.rc

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\version.mak
# End Source File
# End Group
# Begin Source File

SOURCE=.\CopyDLKW.reg
# End Source File
# End Target
# End Project
