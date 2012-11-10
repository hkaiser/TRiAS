# Microsoft Developer Studio Project File - Name="Colors" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Colors - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Colors.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Colors.mak" CFG="Colors - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Colors - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Colors - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Colors - Win32 Release"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ebn.lib ospace5r.lib /nologo /dll /debug /machine:I386 /out:".\Release\Colors.ebn" /subsystem:windows,4.0
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying target to destination ...
TargetDir=.\Release
TargetPath=.\Release\Colors.ebn
TargetName=Colors
InputPath=.\Release\Colors.ebn
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).ebn" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASDIR_R) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_R) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Colors - Win32 Debug"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 ebn.lib ospace5d.lib /nologo /dll /debug /machine:I386 /out:".\Debug\Colorsd.ebn" /subsystem:windows,4.0
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying target to destination ...
TargetDir=.\Debug
TargetPath=.\Debug\Colorsd.ebn
TargetName=Colorsd
InputPath=.\Debug\Colorsd.ebn
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).ebn" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASDIR_D) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_D) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "Colors - Win32 Release"
# Name "Colors - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\ColorLookUp.cpp
# End Source File
# Begin Source File

SOURCE=.\Colors.cpp
# End Source File
# Begin Source File

SOURCE=.\Colors.def
# End Source File
# Begin Source File

SOURCE=.\Colors.idl

!IF  "$(CFG)" == "Colors - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\Colors.idl

BuildCmds= \
	midl Colors.idl \
	xcopy /F Colors.h $(TRIASINCLUDE) \
	xcopy /F Colors_i.c $(TRIASINCLUDE) \
	

"Colors.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Colors.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Colors_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Colors - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\Colors.idl

BuildCmds= \
	midl Colors.idl \
	xcopy /F Colors.h $(TRIASINCLUDE) \
	xcopy /F Colors_i.c $(TRIASINCLUDE) \
	

"Colors.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Colors.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Colors_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Colors.rc
# End Source File
# Begin Source File

SOURCE=.\ColorsExt.cpp
# End Source File
# Begin Source File

SOURCE=.\DoubleColor.cpp
# End Source File
# Begin Source File

SOURCE=.\Jumptab.cpp
# End Source File
# Begin Source File

SOURCE=.\rgb_hsb2.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\ColorLookUp.h
# End Source File
# Begin Source File

SOURCE=.\ColorsExt.h
# End Source File
# Begin Source File

SOURCE=.\DoubleColor.h
# End Source File
# Begin Source File

SOURCE=.\jumptab.h
# End Source File
# Begin Source File

SOURCE=.\rgb_hsb2.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.mak;*.tpl"
# Begin Source File

SOURCE=.\COLORS.TPL

!IF  "$(CFG)" == "Colors - Win32 Release"

USERDEP__COLOR="makefile"	
# Begin Custom Build - Generating version information ...
InputPath=.\COLORS.TPL

"Colors.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake /nologo /f makefile Colors.def

# End Custom Build

!ELSEIF  "$(CFG)" == "Colors - Win32 Debug"

USERDEP__COLOR="makefile"	
# Begin Custom Build - Generating version information ...
InputPath=.\COLORS.TPL

"Colors.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake /nologo /f makefile Colors.def

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Res\Colorsp.tpl

!IF  "$(CFG)" == "Colors - Win32 Release"

USERDEP__COLORS="makefile"	
# Begin Custom Build - Generating version information ...
InputPath=.\Res\Colorsp.tpl

"res\Colors.rc2" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake /nologo /f makefile res\Colors.rc2

# End Custom Build

!ELSEIF  "$(CFG)" == "Colors - Win32 Debug"

USERDEP__COLORS="makefile"	
# Begin Custom Build - Generating version information ...
InputPath=.\Res\Colorsp.tpl

"res\Colors.rc2" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake /nologo /f makefile res\Colors.rc2

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Res\Colorsv.tpl

!IF  "$(CFG)" == "Colors - Win32 Release"

USERDEP__COLORSV="makefile"	
# Begin Custom Build - Generating version information ...
InputPath=.\Res\Colorsv.tpl

"res\Colors.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake /nologo /f makefile res\Colors.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "Colors - Win32 Debug"

USERDEP__COLORSV="makefile"	
# Begin Custom Build - Generating version information ...
InputPath=.\Res\Colorsv.tpl

"res\Colors.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake /nologo /f makefile res\Colors.rcv

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# End Group
# Begin Group "Registry Scripts"

# PROP Default_Filter "*.rgs"
# Begin Source File

SOURCE=.\Res\ColorLookUp.rgs
# End Source File
# Begin Source File

SOURCE=.\Res\DoubleColor.rgs
# End Source File
# End Group
# End Target
# End Project
