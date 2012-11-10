# Microsoft Developer Studio Project File - Name="CvrtCoords" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=CvrtCoords - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CvrtCoords.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CvrtCoords.mak" CFG="CvrtCoords - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CvrtCoords - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "CvrtCoords - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CvrtCoords - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /Zi /O2 /D "WIN32" /D "NDEBUG" /D "_AFXDLL" /D "_MBCS" /D "_CONSOLE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:console /debug /machine:I386

!ELSEIF  "$(CFG)" == "CvrtCoords - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_AFXDLL" /D "_MBCS" /D "_CONSOLE" /Fp"Debug/CvrtCoordsd.pch" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:console /debug /machine:I386 /out:"Debug/CvrtCoordsd.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "CvrtCoords - Win32 Release"
# Name "CvrtCoords - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CvrtCoords.cpp
# End Source File
# Begin Source File

SOURCE=.\CvrtCoords.idl

!IF  "$(CFG)" == "CvrtCoords - Win32 Release"

# ADD MTL /tlb "./CvrtCoords.tlb"
# SUBTRACT MTL /mktyplib203

!ELSEIF  "$(CFG)" == "CvrtCoords - Win32 Debug"

# ADD MTL /tlb "./CvrtCoords.tlb" /h "" /iid "" /Oicf
# SUBTRACT MTL /mktyplib203

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CvrtCoords.rc
# End Source File
# Begin Source File

SOURCE=.\CvrtCoordsApp.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TransformCallback.cpp
# End Source File
# Begin Source File

SOURCE=.\Usage.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BnaCoordSystems.h
# End Source File
# Begin Source File

SOURCE=.\CvrtCoords.h
# End Source File
# Begin Source File

SOURCE=.\CvrtCoordsApp.h
# End Source File
# Begin Source File

SOURCE=.\CvrtCoordsConfig.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TransformCallback.h
# End Source File
# Begin Source File

SOURCE=.\TransformLineOfTextEngine.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\TransformCallback.rgs
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.mak;*.tpl"
# Begin Source File

SOURCE=.\res\copystrt.tpl

!IF  "$(CFG)" == "CvrtCoords - Win32 Release"

# PROP Ignore_Default_Tool 1
USERDEP__COPYS="version.mak"	
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\res\copystrt.tpl

"res\copystr.rct" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak res\copystr.rct

# End Custom Build

!ELSEIF  "$(CFG)" == "CvrtCoords - Win32 Debug"

# PROP Ignore_Default_Tool 1
USERDEP__COPYS="version.mak"	
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\res\copystrt.tpl

"res\copystr.rct" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak res\copystr.rct

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\CvrtCoordsv.tpl

!IF  "$(CFG)" == "CvrtCoords - Win32 Release"

# PROP Ignore_Default_Tool 1
USERDEP__CVRTC="version.mak"	
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\res\CvrtCoordsv.tpl

"res\CvrtCoords.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak res\CvrtCoords.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "CvrtCoords - Win32 Debug"

# PROP Ignore_Default_Tool 1
USERDEP__CVRTC="version.mak"	
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\res\CvrtCoordsv.tpl

"res\CvrtCoords.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak res\CvrtCoords.rcv

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\version.mak
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# End Group
# End Target
# End Project
