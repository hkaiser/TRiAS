# Microsoft Developer Studio Project File - Name="PolygisPMF" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=PolygisPMF - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "PolygisPMF.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "PolygisPMF.mak" CFG="PolygisPMF - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "PolygisPMF - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "PolygisPMF - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/TRiAS/TRiAS/Exportfilter/PolyGIS PMF", QRKBAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "PolygisPMF - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "_Debug"
# PROP Intermediate_Dir "_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /WX /GX /Zi /Od /D "_MBCS" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# SUBTRACT CPP /u
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 tfrm32d.lib cont50d.lib delayimp.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"_Debug/PolygisPMFd.flt"
# Begin Custom Build - Benutzerdefinierte Build-Stufe wird für $(InputPath) ausgeführt
OutDir=.\_Debug
TargetName=PolygisPMFd
InputPath=.\_Debug\PolygisPMFd.flt
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).flt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(OutDir)\$(TargetName).flt" "$(TRIASDIR_D)" 
	xcopy /F "$(OutDir)\$(TargetName).pdb" "$(TRIASDIR_D)" 
	
# End Custom Build
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Cmds=nmake -nologo -f Version.mak CFG=_DEBUG VERSION
# End Special Build Tool

!ELSEIF  "$(CFG)" == "PolygisPMF - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "PolygisPMF___Win32_Release"
# PROP BASE Intermediate_Dir "PolygisPMF___Win32_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "_Release"
# PROP Intermediate_Dir "_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MD /W3 /GX /Zi /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /Zi /O1 /D "_MBCS" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 delayimp.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"_Release/PolygisPMF.flt"
# ADD LINK32 tfrmwork.lib containr.lib delayimp.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"_Release/PolygisPMF.flt"
# Begin Custom Build - Die Registrierung wird durchgeführt
OutDir=.\_Release
TargetName=PolygisPMF
InputPath=.\_Release\PolygisPMF.flt
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).flt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(OutDir)\$(TargetName).flt" "$(TRIASDIR_R)" 
	xcopy /F "$(OutDir)\$(TargetName).pdb" "$(TRIASDIR_R)" 
	
# End Custom Build
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Cmds=nmake -nologo -f Version.mak CFG=NDEBUG VERSION
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "PolygisPMF - Win32 Debug"
# Name "PolygisPMF - Win32 Release"
# Begin Group "PolyGIS PMF"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\PolygisCAP.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\PolygisDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\PolygisEXP.CXX
# End Source File
# Begin Source File

SOURCE=.\PolygisPMF.rc
# End Source File
# Begin Source File

SOURCE=.\PolygisPMFExport.cpp
# End Source File
# Begin Source File

SOURCE=.\PolygisTree.cpp
# End Source File
# Begin Source File

SOURCE=.\STRUTIL.CXX
# End Source File
# End Group
# Begin Group "Header -Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\PMFExp.h
# End Source File
# Begin Source File

SOURCE=.\PolygisDLG.hxx
# End Source File
# Begin Source File

SOURCE=.\Polygisexp.hxx

!IF  "$(CFG)" == "PolygisPMF - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "PolygisPMF - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PolygisPMF.h
# End Source File
# Begin Source File

SOURCE=.\PolygisPMFExport.h
# End Source File
# Begin Source File

SOURCE=.\PolygisPMFImpl.h
# End Source File
# Begin Source File

SOURCE=.\PolygisTree.hxx
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Ressourcendateien"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\MSG00407.bin
# End Source File
# Begin Source File

SOURCE=.\res\MSG00409.bin
# End Source File
# Begin Source File

SOURCE=.\PolygisPMFExport.rgs
# End Source File
# End Group
# Begin Group "Generated Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\PolygisPMF.def
# End Source File
# Begin Source File

SOURCE=.\PolygisPMF.rcv
# End Source File
# Begin Source File

SOURCE=.\PolygisPMF.ver
# End Source File
# End Group
# Begin Group "Help Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Help\PolygisPMF.d

!IF  "$(CFG)" == "PolygisPMF - Win32 Debug"

# Begin Custom Build
InputPath=.\Help\PolygisPMF.d
InputName=PolygisPMF

"$(TRIASINCLUDE)\help\$(InputName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak CFG=_DEBUG

# End Custom Build

!ELSEIF  "$(CFG)" == "PolygisPMF - Win32 Release"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\Help\PolygisPMF.d
InputName=PolygisPMF

"$(TRIASINCLUDE)\help\$(InputName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak CFG=NDEBUG

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PolygisPMF.mc

!IF  "$(CFG)" == "PolygisPMF - Win32 Debug"

# Begin Custom Build
InputPath=.\PolygisPMF.mc

BuildCmds= \
	nmake -nologo -f version.mak CFG=_DEBUG

".\PolygisPMF.hmc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\res\msg00407.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\res\msg00409.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "PolygisPMF - Win32 Release"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\PolygisPMF.mc

BuildCmds= \
	nmake -nologo -f version.mak CFG=NDEBUG

".\PolygisPMF.hmc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\res\msg00407.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\res\msg00409.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "DLL Data"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\ExportInl.cpp
# End Source File
# Begin Source File

SOURCE=.\PolygisPMF.cpp
# End Source File
# Begin Source File

SOURCE=.\PolygisPMF.idl

!IF  "$(CFG)" == "PolygisPMF - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\PolygisPMF.idl

BuildCmds= \
	nmake -nologo -f version.mak CFG=_DEBUG

".\PolygisPMF.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\PolygisPMF.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASTLB)\PolygisPMF.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "PolygisPMF - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\PolygisPMF.idl

BuildCmds= \
	nmake -nologo -f version.mak CFG=NDEBUG

".\PolygisPMF.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\PolygisPMF.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASTLB)\PolygisPMF.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PolygisPMFImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Version.mak

!IF  "$(CFG)" == "PolygisPMF - Win32 Debug"

# Begin Custom Build
InputPath=.\Version.mak

BuildCmds= \
	nmake -nologo -f version.mak CFG=_DEBUG

".\PolygisPMF.ver" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\PolygisPMF.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\PolygisPMF.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "PolygisPMF - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\Version.mak

BuildCmds= \
	nmake -nologo -f version.mak CFG=NDEBUG

".\PolygisPMF.ver" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\PolygisPMF.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\PolygisPMF.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=..\PropNamex.cpp
# End Source File
# Begin Source File

SOURCE=..\Registry.cpp
# End Source File
# End Target
# End Project
