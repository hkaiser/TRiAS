# Microsoft Developer Studio Project File - Name="Triasarc" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Triasarc - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TRIASARC.MAK".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TRIASARC.MAK" CFG="Triasarc - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Triasarc - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Triasarc - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Triasarc - Win32 Release"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\WinRel"
# PROP BASE Intermediate_Dir ".\WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "_Release"
# PROP Intermediate_Dir "_Release"
# PROP Ignore_Export_Lib 0
F90=fl32.exe
# ADD BASE CPP /nologo /Zp1 /MT /W3 /GX /Ox /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "__CV__" /D "STRICT" /D "MSWIND" /D "DLL" /D "__XT" /D "_USRDLL" /D "_MBCS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /I "$(TRIASINCLUDE)\hpp" /I "$(TRIASINCLUDE)\..\FrameWrk\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 oldnames.lib ldllcew.lib framelib.lib containr.lib /nologo /subsystem:windows /dll /map:"FULL" /machine:IX86
# ADD LINK32 delayimp.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:IX86 /out:"_RELEASE/TRIASARC.flt" /delayload:crp32dll.dll /delayload:ole32.dll /delayload:oleaut32.dll
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build
OutDir=.\_Release
TargetName=TRIASARC
InputPath=.\_RELEASE\TRIASARC.flt
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).flt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(OutDir)\$(TargetName).flt" "$(TRIASDIR_R)" 
	xcopy /F "$(OutDir)\$(TargetName).pdb" "$(TRIASDIR_R)" 
	
# End Custom Build
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Cmds=nmake -nologo -f Version.mak CFG=NDEBUG VERSION
# End Special Build Tool

!ELSEIF  "$(CFG)" == "Triasarc - Win32 Debug"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\WinDebug"
# PROP BASE Intermediate_Dir ".\WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "_Debug"
# PROP Intermediate_Dir "_Debug"
# PROP Ignore_Export_Lib 0
F90=fl32.exe
# ADD BASE CPP /nologo /Zp1 /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "__CV__" /D "STRICT" /D "MSWIND" /D "DLL" /D "__XT" /D "_USRDLL" /D "_MBCS" /FR /YX /c
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
# ADD BASE LINK32 oldnames.lib ldllcew.lib framelib.lib containr.lib /nologo /subsystem:windows /dll /map:"FULL" /debug /machine:IX86
# ADD LINK32 tfrm32d.lib cont50d.lib delayimp.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:IX86 /out:"_DEBUG/TRIASARCD.flt" /delayload:crp32dll.dll /delayload:ole32.dll /delayload:oleaut32.dll /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none /incremental:no
# Begin Custom Build
OutDir=.\_Debug
TargetName=TRIASARCD
InputPath=.\_DEBUG\TRIASARCD.flt
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

# Name "Triasarc - Win32 Release"
# Name "Triasarc - Win32 Debug"
# Begin Group "TRiASArc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ArcExp.cxx
# End Source File
# Begin Source File

SOURCE=.\COMMFIL.CXX
# End Source File
# Begin Source File

SOURCE=.\COVER.CXX
# End Source File
# Begin Source File

SOURCE=.\Cover.hxx
# End Source File
# Begin Source File

SOURCE=.\COVNAME.CXX
# End Source File
# Begin Source File

SOURCE=.\Covname.hxx
# End Source File
# Begin Source File

SOURCE=.\cpl_conv.cpp
# End Source File
# Begin Source File

SOURCE=.\cpl_error.cpp
# End Source File
# Begin Source File

SOURCE=.\cpl_vsisimple.cpp
# End Source File
# Begin Source File

SOURCE=.\e00read.cpp
# End Source File
# Begin Source File

SOURCE=.\e00write.cpp
# End Source File
# Begin Source File

SOURCE=.\EXPCAPS.CXX
# End Source File
# Begin Source File

SOURCE=.\EXPPARAM.CXX
# End Source File
# Begin Source File

SOURCE=.\Expparam.hxx
# End Source File
# Begin Source File

SOURCE=.\FILEOBJ.CXX
# End Source File
# Begin Source File

SOURCE=.\Fileobj.hxx
# End Source File
# Begin Source File

SOURCE=.\GEO.CXX
# End Source File
# Begin Source File

SOURCE=.\Geo.hxx
# End Source File
# Begin Source File

SOURCE=.\HELPTEXT.CXX
# End Source File
# Begin Source File

SOURCE=.\Helptext.hxx
# End Source File
# Begin Source File

SOURCE=.\IDENT.CXX
# End Source File
# Begin Source File

SOURCE=.\Ident.hxx
# End Source File
# Begin Source File

SOURCE=.\INFO.CXX
# End Source File
# Begin Source File

SOURCE=.\Info.hxx
# End Source File
# Begin Source File

SOURCE=.\MERKMDES.CXX
# End Source File
# Begin Source File

SOURCE=.\Merkmdes.hxx
# End Source File
# Begin Source File

SOURCE=.\MERKNAME.CXX
# End Source File
# Begin Source File

SOURCE=.\Merkname.hxx
# End Source File
# Begin Source File

SOURCE=.\NAMEEDIT.CXX
# End Source File
# Begin Source File

SOURCE=.\Nameedit.hxx
# End Source File
# Begin Source File

SOURCE=.\NUMEDIT.CXX
# End Source File
# Begin Source File

SOURCE=.\Numedit.hxx
# End Source File
# Begin Source File

SOURCE=..\Registry.cpp
# End Source File
# Begin Source File

SOURCE=.\RESOURCE.CXX
# End Source File
# Begin Source File

SOURCE=.\SECTION.CXX
# End Source File
# Begin Source File

SOURCE=.\Section.hxx
# End Source File
# Begin Source File

SOURCE=.\TRiASArcExport.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASArcExport.h
# End Source File
# Begin Source File

SOURCE=.\VISINFO.CXX
# End Source File
# End Group
# Begin Group "DLL Data"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\ExportInl.cpp
# End Source File
# Begin Source File

SOURCE=.\Stdafx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Stdafx.h
# End Source File
# Begin Source File

SOURCE=.\TRiASArc.cpp
# End Source File
# Begin Source File

SOURCE=.\Triasarc.hxx
# End Source File
# Begin Source File

SOURCE=.\TRiASArc.idl

!IF  "$(CFG)" == "Triasarc - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\TRiASArc.idl

BuildCmds= \
	nmake -nologo -f version.mak CFG=NDEBUG

".\Triasarc.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Triasarc.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASTLB)\Triasarc.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Triasarc - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\TRiASArc.idl

BuildCmds= \
	nmake -nologo -f version.mak CFG=_DEBUG

".\Triasarc.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Triasarc.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASTLB)\Triasarc.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TRiASArcImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASArcImpl.h
# End Source File
# Begin Source File

SOURCE=.\Version.mak

!IF  "$(CFG)" == "Triasarc - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\Version.mak

BuildCmds= \
	nmake -nologo -f version.mak CFG=NDEBUG

".\Triasarc.ver" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Triasarc.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Triasarc.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Triasarc - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\Version.mak

BuildCmds= \
	nmake -nologo -f version.mak CFG=_DEBUG

".\Triasarc.ver" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Triasarc.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Triasarc.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\AATFORMT.DAT
# End Source File
# Begin Source File

SOURCE=.\BNDFORMT.DAT
# End Source File
# Begin Source File

SOURCE=.\res\MSG00407.bin
# End Source File
# Begin Source File

SOURCE=.\PATFORMT.DAT
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\TICFORMT.DAT
# End Source File
# Begin Source File

SOURCE=.\Triasarc.hr
# End Source File
# Begin Source File

SOURCE=.\TRIASARC.RC
# End Source File
# Begin Source File

SOURCE=.\TRiASArcExport.rgs
# End Source File
# End Group
# Begin Group "Generated Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TRIASARC.DEF
# End Source File
# Begin Source File

SOURCE=.\TRIASARC.RCV
# End Source File
# Begin Source File

SOURCE=.\TRiASARC.ver
# End Source File
# End Group
# Begin Group "Help Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\help\TRiASArc.d

!IF  "$(CFG)" == "Triasarc - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\help\TRiASArc.d
InputName=TRiASArc

"$(TRIASINCLUDE)\help\$(InputName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak CFG=NDEBUG

# End Custom Build

!ELSEIF  "$(CFG)" == "Triasarc - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\help\TRiASArc.d
InputName=TRiASArc

"$(TRIASINCLUDE)\help\$(InputName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak CFG=_DEBUG

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TRiASArc.mc

!IF  "$(CFG)" == "Triasarc - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\TRiASArc.mc

BuildCmds= \
	nmake -nologo -f version.mak CFG=NDEBUG

".\Triasarc.hmc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\res\msg00407.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\res\msg00409.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Triasarc - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\TRiASArc.mc

BuildCmds= \
	nmake -nologo -f version.mak CFG=_DEBUG

".\Triasarc.hmc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\res\msg00407.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\res\msg00409.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=..\PropNamex.cpp
# End Source File
# End Target
# End Project
