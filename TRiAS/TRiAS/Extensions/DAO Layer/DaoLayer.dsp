# Microsoft Developer Studio Project File - Name="DaoLayer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=DaoLayer - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DaoLayer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DaoLayer.mak" CFG="DaoLayer - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DaoLayer - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "DaoLayer - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/TRiAS/TRiAS/Extensions/DAO Layer", TWCAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DaoLayer - Win32 Release"

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
F90=fl32.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "EBWIN32" /D DLLEXPORT=__declspec(dllexport) /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL" /d "_USE_DEFAULT_PROPERTYGET"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ebn.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:".\Release\DaoLayer.ebn"
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying Target to Destination ...
OutDir=.\Release
TargetPath=.\Release\DaoLayer.ebn
TargetName=DaoLayer
InputPath=.\Release\DaoLayer.ebn
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).ebn" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASDIR_R) 
	xcopy /F "$(OutDir)/$(TargetName).pdb" $(TRIASDIR_R) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "DaoLayer - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "EBWIN32" /D DLLEXPORT=__declspec(dllexport) /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL" /d "_USE_DEFAULT_PROPERTYGET"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 ebn.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:".\Debug\DaoLayed.ebn"
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying Target to Destination ...
OutDir=.\Debug
TargetPath=.\Debug\DaoLayed.ebn
TargetName=DaoLayed
InputPath=.\Debug\DaoLayed.ebn
SOURCE="$(InputPath)"

BuildCmds= \
	xcopy /F "$(TargetPath)" $(TRIASDIR_D) \
	xcopy /F "$(OutDir)\$(TargetName).pdb" $(TRIASDIR_D) \
	

"$(TRIASDIR_D)\$(TargetName).ebn" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASDIR_D)\$(TargetName).pdb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# Begin Target

# Name "DaoLayer - Win32 Release"
# Name "DaoLayer - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\Daoextf.cpp

!IF  "$(CFG)" == "DaoLayer - Win32 Release"

!ELSEIF  "$(CFG)" == "DaoLayer - Win32 Debug"

# ADD CPP /Gi

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\Daoextp.rc
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Daolayed.def

!IF  "$(CFG)" == "DaoLayer - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "DaoLayer - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DaoLayer.cpp
# End Source File
# Begin Source File

SOURCE=.\DaoLayer.def

!IF  "$(CFG)" == "DaoLayer - Win32 Release"

!ELSEIF  "$(CFG)" == "DaoLayer - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DaoLayer.rc
# End Source File
# Begin Source File

SOURCE=.\Dbdao.cpp
# End Source File
# Begin Source File

SOURCE=.\jumptab.cpp
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\strcvrt.cpp
# End Source File
# Begin Source File

SOURCE=.\WinVersn.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\Daoextf.h
# End Source File
# Begin Source File

SOURCE=.\DaoLayer.h
# End Source File
# Begin Source File

SOURCE=.\ebargs.h
# End Source File
# Begin Source File

SOURCE=.\jumptab.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\strcvrt.h
# End Source File
# Begin Source File

SOURCE=.\WinVersn.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\daoextf.rc
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.mak,*.tpl"
# Begin Source File

SOURCE=.\res\Daoextp.tpl

!IF  "$(CFG)" == "DaoLayer - Win32 Release"

# Begin Custom Build
InputPath=.\res\Daoextp.tpl

"res\daoextf.rc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f daolay16.mak -nologo res\daoextf.rc

# End Custom Build

!ELSEIF  "$(CFG)" == "DaoLayer - Win32 Debug"

USERDEP__DAOEX="daolay16.mak"	
# Begin Custom Build
InputPath=.\res\Daoextp.tpl

"res\daoextf.rc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f daolay16.mak -nologo res\daoextf.rc

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DAOLAY16.MAK
# End Source File
# Begin Source File

SOURCE=.\daolayer.tpl

!IF  "$(CFG)" == "DaoLayer - Win32 Release"

# Begin Custom Build
InputPath=.\daolayer.tpl

"daolayer.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f daolay16.mak -nologo daolayer.def

# End Custom Build

!ELSEIF  "$(CFG)" == "DaoLayer - Win32 Debug"

USERDEP__DAOLA="daolay16.mak"	
# Begin Custom Build
InputPath=.\daolayer.tpl

"daolayed.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f daolay16.mak -nologo daolayed.def

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DAOLAYV.tpl

!IF  "$(CFG)" == "DaoLayer - Win32 Release"

# Begin Custom Build
InputPath=.\DAOLAYV.tpl

"daolayer.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f daolay16.mak -nologo daolayer.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "DaoLayer - Win32 Debug"

USERDEP__DAOLAY="daolay16.mak"	
# Begin Custom Build
InputPath=.\DAOLAYV.tpl

"daolayer.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f daolay16.mak -nologo daolayer.rcv

# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
