# Microsoft Developer Studio Project File - Name="Acaddxf" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Acaddxf - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ACADDXF.MAK".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ACADDXF.MAK" CFG="Acaddxf - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Acaddxf - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Acaddxf - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/TRiAS/TRiAS/Exportfilter/AutoCAD DXF", GBGAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Acaddxf - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\WinRel"
# PROP BASE Intermediate_Dir ".\WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "_Release"
# PROP Intermediate_Dir "_Release"
# PROP Ignore_Export_Lib 0
F90=fl32.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /I "$(TRIASINCLUDE)\hpp" /I "$(TRIASINCLUDE)\..\FrameWrk\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 tfrmwork.lib containr.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib delayimp.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"_Release/ACADDXF.flt" /delayload:crp32dll.dll /delayload:ole32.dll /delayload:oleaut32.dll
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build
OutDir=.\_Release
TargetName=ACADDXF
InputPath=.\_Release\ACADDXF.flt
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).flt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(OutDir)\$(TargetName).flt" "$(TRIASDIR_R)" 
	xcopy /F "$(OutDir)\$(TargetName).pdb" "$(TRIASDIR_R)" 
	
# End Custom Build
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Cmds=nmake -nologo -f Version.mak CFG=NDEBUG VERSION
# End Special Build Tool

!ELSEIF  "$(CFG)" == "Acaddxf - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\WinDebug"
# PROP BASE Intermediate_Dir ".\WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "_Debug"
# PROP Intermediate_Dir "_Debug"
# PROP Ignore_Export_Lib 0
F90=fl32.exe
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /GX /Zi /Od /I "$(TRIASINCLUDE)\hpp" /I "$(TRIASINCLUDE)\..\FrameWrk\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 tfrm32d.lib cont50d.lib delayimp.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib /nologo /dll /debug /machine:I386 /out:"_Debug/ACADDXFD.flt" /delayload:crp32dll.dll /delayload:ole32.dll /delayload:oleaut32.dll /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none /incremental:no
# Begin Custom Build
OutDir=.\_Debug
TargetName=ACADDXFD
InputPath=.\_Debug\ACADDXFD.flt
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).flt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(OutDir)\$(TargetName).flt" "$(TRIASDIR_D)" 
	xcopy /F "$(OutDir)\$(TargetName).pdb" "$(TRIASDIR_D)" 
	
# End Custom Build
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Cmds=nmake -nologo -f Version.mak CFG=_DEBUG VERSION
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "Acaddxf - Win32 Release"
# Name "Acaddxf - Win32 Debug"
# Begin Group "AcadDXF"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Acaddxf.hxx
# End Source File
# Begin Source File

SOURCE=.\AcadDXFExport.cpp
# End Source File
# Begin Source File

SOURCE=.\AcadDXFExport.h
# End Source File
# Begin Source File

SOURCE=.\AcadExp.cpp
# End Source File
# Begin Source File

SOURCE=.\COMMFIL.CXX
# End Source File
# Begin Source File

SOURCE=.\EXPCAPS.CXX
# End Source File
# Begin Source File

SOURCE=.\IDENTDES.CXX
# End Source File
# Begin Source File

SOURCE=.\Identdes.hxx
# End Source File
# Begin Source File

SOURCE=.\MERKMDES.CXX
# End Source File
# Begin Source File

SOURCE=.\Merkmdes.hxx
# End Source File
# Begin Source File

SOURCE=.\PALETTE.CXX
# End Source File
# Begin Source File

SOURCE=.\RESOURCE.CXX
# End Source File
# Begin Source File

SOURCE=.\STRUTIL.CXX
# End Source File
# Begin Source File

SOURCE=.\VISINFO.CXX
# End Source File
# End Group
# Begin Group "DLL Data"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AcadDXF.cpp
# End Source File
# Begin Source File

SOURCE=.\AcadDXF.idl

!IF  "$(CFG)" == "Acaddxf - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\AcadDXF.idl

BuildCmds= \
	nmake -nologo -f version.mak CFG=NDEBUG

".\Acaddxf.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Acaddxf.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASTLB)\Acaddxf.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Acaddxf - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\AcadDXF.idl

BuildCmds= \
	nmake -nologo -f version.mak CFG=_DEBUG

".\Acaddxf.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Acaddxf.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASTLB)\Acaddxf.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\AcadDXFImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\AcadDXFImpl.h
# End Source File
# Begin Source File

SOURCE=..\ExportInl.cpp
# End Source File
# Begin Source File

SOURCE=.\stdafx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\stdafx.h
# End Source File
# Begin Source File

SOURCE=.\Version.mak

!IF  "$(CFG)" == "Acaddxf - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\Version.mak

BuildCmds= \
	nmake -nologo -f version.mak CFG=NDEBUG

".\Acaddxf.ver" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Acaddxf.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Acaddxf.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Acaddxf - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\Version.mak

BuildCmds= \
	nmake -nologo -f version.mak CFG=_DEBUG

".\Acaddxf.ver" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Acaddxf.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Acaddxf.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Group "res"

# PROP Default_Filter ""
# Begin Group "Symbols"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\171.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\171.SBL
# End Source File
# Begin Source File

SOURCE=.\172.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\172.SBL
# End Source File
# Begin Source File

SOURCE=.\173.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\173.SBL
# End Source File
# Begin Source File

SOURCE=.\174.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\174.SBL
# End Source File
# Begin Source File

SOURCE=.\175.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\175.SBL
# End Source File
# Begin Source File

SOURCE=.\176.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\176.SBL
# End Source File
# Begin Source File

SOURCE=.\177.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\177.SBL
# End Source File
# Begin Source File

SOURCE=.\178.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\178.SBL
# End Source File
# Begin Source File

SOURCE=.\180.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\180.SBL
# End Source File
# Begin Source File

SOURCE=.\181.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\181.SBL
# End Source File
# Begin Source File

SOURCE=.\182.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\182.SBL
# End Source File
# Begin Source File

SOURCE=.\183.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\183.SBL
# End Source File
# Begin Source File

SOURCE=.\184.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\184.SBL
# End Source File
# Begin Source File

SOURCE=.\185.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\185.SBL
# End Source File
# Begin Source File

SOURCE=.\186.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\186.SBL
# End Source File
# Begin Source File

SOURCE=.\187.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\187.SBL
# End Source File
# Begin Source File

SOURCE=.\188.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\188.SBL
# End Source File
# Begin Source File

SOURCE=.\189.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\189.SBL
# End Source File
# Begin Source File

SOURCE=.\190.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\190.SBL
# End Source File
# Begin Source File

SOURCE=.\191.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\191.SBL
# End Source File
# Begin Source File

SOURCE=.\192.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\192.SBL
# End Source File
# Begin Source File

SOURCE=.\193.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\193.SBL
# End Source File
# Begin Source File

SOURCE=.\194.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\194.SBL
# End Source File
# Begin Source File

SOURCE=.\195.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\195.SBL
# End Source File
# Begin Source File

SOURCE=.\196.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\196.SBL
# End Source File
# Begin Source File

SOURCE=.\197.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\197.SBL
# End Source File
# Begin Source File

SOURCE=.\198.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\198.SBL
# End Source File
# Begin Source File

SOURCE=.\199.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\199.SBL
# End Source File
# Begin Source File

SOURCE=.\200.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\200.SBL
# End Source File
# Begin Source File

SOURCE=.\201.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\201.SBL
# End Source File
# Begin Source File

SOURCE=.\202.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\202.SBL
# End Source File
# Begin Source File

SOURCE=.\203.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\203.SBL
# End Source File
# Begin Source File

SOURCE=.\204.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\204.SBL
# End Source File
# Begin Source File

SOURCE=.\205.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\205.SBL
# End Source File
# Begin Source File

SOURCE=.\206.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\206.SBL
# End Source File
# Begin Source File

SOURCE=.\207.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\207.SBL
# End Source File
# Begin Source File

SOURCE=.\208.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\208.SBL
# End Source File
# Begin Source File

SOURCE=.\209.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\209.SBL
# End Source File
# Begin Source File

SOURCE=.\21.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\21.SBL
# End Source File
# Begin Source File

SOURCE=.\210.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\210.SBL
# End Source File
# Begin Source File

SOURCE=.\211.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\211.SBL
# End Source File
# Begin Source File

SOURCE=.\212.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\212.SBL
# End Source File
# Begin Source File

SOURCE=.\213.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\213.SBL
# End Source File
# Begin Source File

SOURCE=.\214.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\214.SBL
# End Source File
# Begin Source File

SOURCE=.\215.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\215.SBL
# End Source File
# Begin Source File

SOURCE=.\216.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\216.SBL
# End Source File
# Begin Source File

SOURCE=.\217.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\217.SBL
# End Source File
# Begin Source File

SOURCE=.\218.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\218.SBL
# End Source File
# Begin Source File

SOURCE=.\219.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\219.SBL
# End Source File
# Begin Source File

SOURCE=.\220.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\220.SBL
# End Source File
# Begin Source File

SOURCE=.\222.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\222.SBL
# End Source File
# Begin Source File

SOURCE=.\228.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\228.SBL
# End Source File
# Begin Source File

SOURCE=.\229.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\229.SBL
# End Source File
# Begin Source File

SOURCE=.\230.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\230.SBL
# End Source File
# Begin Source File

SOURCE=.\231.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\231.SBL
# End Source File
# Begin Source File

SOURCE=.\232.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\232.SBL
# End Source File
# Begin Source File

SOURCE=.\233.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\233.SBL
# End Source File
# Begin Source File

SOURCE=.\234.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\234.SBL
# End Source File
# Begin Source File

SOURCE=.\235.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\235.SBL
# End Source File
# Begin Source File

SOURCE=.\236.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\236.SBL
# End Source File
# Begin Source File

SOURCE=.\250.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\250.SBL
# End Source File
# Begin Source File

SOURCE=.\251.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\251.SBL
# End Source File
# Begin Source File

SOURCE=.\252.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\252.SBL
# End Source File
# Begin Source File

SOURCE=.\26.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\26.SBL
# End Source File
# Begin Source File

SOURCE=.\3.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\3.SBL
# End Source File
# Begin Source File

SOURCE=.\47.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\47.SBL
# End Source File
# Begin Source File

SOURCE=.\5.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\5.SBL
# End Source File
# Begin Source File

SOURCE=.\6.sbl
# End Source File
# Begin Source File

SOURCE=.\res\Symbols\6.SBL
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\LINETAB.TPL
# End Source File
# Begin Source File

SOURCE=.\res\VISINFO.TPL
# End Source File
# End Group
# Begin Source File

SOURCE=.\ACADDXF.RC
# End Source File
# Begin Source File

SOURCE=.\res\msg00407.bin
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# End Group
# Begin Group "Help Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\help\AcadDXF.d

!IF  "$(CFG)" == "Acaddxf - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\help\AcadDXF.d
InputName=AcadDXF

"$(TRIASINCLUDE)\help\$(InputName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak CFG=NDEBUG

# End Custom Build

!ELSEIF  "$(CFG)" == "Acaddxf - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\help\AcadDXF.d
InputName=AcadDXF

"$(TRIASINCLUDE)\help\$(InputName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak CFG=_DEBUG

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\AcadDXF.mc

!IF  "$(CFG)" == "Acaddxf - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\AcadDXF.mc

BuildCmds= \
	nmake -nologo -f version.mak CFG=NDEBUG

".\Acaddxf.hmc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\res\msg00407.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\res\msg00409.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Acaddxf - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\AcadDXF.mc

BuildCmds= \
	nmake -nologo -f version.mak CFG=_DEBUG

".\Acaddxf.hmc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\res\msg00407.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\res\msg00409.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Generated Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ACADDXF.DEF
# End Source File
# Begin Source File

SOURCE=.\AcadDXF.rcv
# End Source File
# Begin Source File

SOURCE=.\AcadDXF.ver
# End Source File
# End Group
# Begin Source File

SOURCE=.\AcadDXFExport.rgs
# End Source File
# Begin Source File

SOURCE=..\PropNamex.cpp
# End Source File
# Begin Source File

SOURCE=..\Registry.cpp
# End Source File
# End Target
# End Project
