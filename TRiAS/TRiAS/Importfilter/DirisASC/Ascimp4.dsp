# Microsoft Developer Studio Project File - Name="Ascimp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Ascimp - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Ascimp4.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Ascimp4.mak" CFG="Ascimp - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Ascimp - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Ascimp - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/TRiAS/TRiAS/Importfilter/DirisASC", FUEAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Ascimp - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\WinRel"
# PROP BASE Intermediate_Dir ".\WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
F90=fl32.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /D "NDEBUG" /D "MSWIND" /D "_WINDOWS" /D "WIN32" /Yu"ascimpp.hpp" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 Ixtatr50.lib tfrmwork.lib containr.lib ospace5r.lib delayimp.lib winmm.lib /nologo /dll /debug /machine:I386 /out:".\Release\ascimp.ext" /delayload:crp32dll.dll /delayload:winmm.dll /delayload:ole32.dll /delayload:oleaut32.dll /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying Target to Destination ...
TargetDir=.\Release
TargetPath=.\Release\ascimp.ext
TargetName=ascimp
InputPath=.\Release\ascimp.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASDIR_R) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_R) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Ascimp - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\WinDebug"
# PROP BASE Intermediate_Dir ".\WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
F90=fl32.exe
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /D "_DEBUG" /D "MSWIND" /D "_WINDOWS" /D "WIN32" /Fp".\Debug\ASCIMPD.pch" /Yu"ascimpp.hpp" /Fd".\Debug\ASCIMPD.pdb" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 Ixtatd50.lib tfrm32d.lib cont50d.lib ospace5d.lib delayimp.lib winmm.lib /nologo /dll /debug /machine:I386 /out:".\Debug\ascimpd.ext" /delayload:crp32dll.dll /delayload:winmm.dll /delayload:ole32.dll /delayload:oleaut32.dll /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying Target to Destination ...
TargetDir=.\Debug
TargetPath=.\Debug\ascimpd.ext
TargetName=ascimpd
InputPath=.\Debug\ascimpd.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASDIR_D) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_D) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "Ascimp - Win32 Release"
# Name "Ascimp - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\ASCIMP.CPP
# End Source File
# Begin Source File

SOURCE=.\ASCIMP.DEF
# End Source File
# Begin Source File

SOURCE=.\ascimp.rc
# End Source File
# Begin Source File

SOURCE=.\ASCIMPIF.CPP
# End Source File
# Begin Source File

SOURCE=.\ASCIMPP.CPP

!IF  "$(CFG)" == "Ascimp - Win32 Release"

# ADD CPP /Yc"ascimpp.hpp"

!ELSEIF  "$(CFG)" == "Ascimp - Win32 Debug"

# ADD CPP /Zi /Yc"ascimpp.hpp"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\asclic.cpp
# End Source File
# Begin Source File

SOURCE=.\ASCPARLT.CPP
# End Source File
# Begin Source File

SOURCE=.\Ascpars.lx

!IF  "$(CFG)" == "Ascimp - Win32 Release"

# Begin Custom Build
InputDir=.
InputPath=.\Ascpars.lx
InputName=Ascpars

"$(InputDir)\$(InputName)l.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	pclex -s -ppclex.sk -l "$(InputPath)" 
	del ascparsl.cpp > nul 
	move ascpars.c "$(InputDir)\$(InputName)l.cpp" > nul 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Ascimp - Win32 Debug"

# Begin Custom Build - Generating Lexer sources ...
InputDir=.
InputPath=.\Ascpars.lx
InputName=Ascpars

"$(InputDir)\$(InputName)l.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	pclex -s -ppclex.sk -l "$(InputPath)" 
	del ascparsl.cpp > nul 
	move ascpars.c "$(InputDir)\$(InputName)l.cpp" > nul 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Ascpars.y

!IF  "$(CFG)" == "Ascimp - Win32 Release"

# Begin Custom Build
InputDir=.
InputPath=.\Ascpars.y
InputName=Ascpars

"$(InputDir)\$(InputName)y.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	pcyacc -Dytab.h -C"$(InputDir)\$(InputName)y.cpp" -n -s "$(InputPath)"

# End Custom Build

!ELSEIF  "$(CFG)" == "Ascimp - Win32 Debug"

# Begin Custom Build - Generating Parser sources ...
InputDir=.
InputPath=.\Ascpars.y
InputName=Ascpars

"$(InputDir)\$(InputName)y.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	pcyacc -Dytab.h -C"$(InputDir)\$(InputName)y.cpp" -n -s "$(InputPath)"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ASCPARSC.CPP
# End Source File
# Begin Source File

SOURCE=.\ASCPARYT.CPP
# End Source File
# Begin Source File

SOURCE=.\RELCONT.CPP
# End Source File
# Begin Source File

SOURCE=.\result.cpp
# End Source File
# Begin Source File

SOURCE=.\status.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\ASCERRS.H
# End Source File
# Begin Source File

SOURCE=.\ASCGUIDS.H
# End Source File
# Begin Source File

SOURCE=.\ascimp.hpp
# End Source File
# Begin Source File

SOURCE=.\AscImpConfig.h
# End Source File
# Begin Source File

SOURCE=.\ASCIMPP.HPP
# End Source File
# Begin Source File

SOURCE=.\Ascpars.h
# End Source File
# Begin Source File

SOURCE=.\INPUT.H
# End Source File
# Begin Source File

SOURCE=.\RELCONT.HPP
# End Source File
# Begin Source File

SOURCE=.\result.hxx
# End Source File
# Begin Source File

SOURCE=.\status.hxx
# End Source File
# Begin Source File

SOURCE=.\YTAB.H
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Res\ascimp.ico
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ASCIMP.TPL

!IF  "$(CFG)" == "Ascimp - Win32 Release"

USERDEP__ASCIM="makefile"	
# Begin Custom Build
InputPath=.\ASCIMP.TPL

"ascimp.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f makefile -nologo ascimp.def

# End Custom Build

!ELSEIF  "$(CFG)" == "Ascimp - Win32 Debug"

USERDEP__ASCIM="makefile"	
# Begin Custom Build
InputPath=.\ASCIMP.TPL

"ascimp.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f makefile -nologo ascimp.def

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ASCIMPV.TPL

!IF  "$(CFG)" == "Ascimp - Win32 Release"

USERDEP__ASCIMP="makefile"	
# Begin Custom Build
InputPath=.\ASCIMPV.TPL

"ascimp.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f makefile -nologo ascimp.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "Ascimp - Win32 Debug"

USERDEP__ASCIMP="makefile"	
# Begin Custom Build
InputPath=.\ASCIMPV.TPL

"ascimp.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f makefile -nologo ascimp.rcv

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# Begin Source File

SOURCE=.\VERSION.TPL

!IF  "$(CFG)" == "Ascimp - Win32 Release"

USERDEP__VERSI="makefile"	
# Begin Custom Build
InputPath=.\VERSION.TPL

"version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f makefile -nologo version.h

# End Custom Build

!ELSEIF  "$(CFG)" == "Ascimp - Win32 Debug"

USERDEP__VERSI="makefile"	
# Begin Custom Build
InputPath=.\VERSION.TPL

"version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f makefile -nologo version.h

# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
